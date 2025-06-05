#include "client.hpp"
#include <iostream>
#include "config.hpp"

using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    Client* client = static_cast<Client*>(glfwGetWindowUserPointer(window));

    if (!client)
        return;

    float aspect = static_cast<float>(width) / height;

    // scene->updateWindow(window);

    client->camera.setAspect(aspect);
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    Client* client = static_cast<Client*>(glfwGetWindowUserPointer(window));

    if (!client)
        return;

    if (!client->isMouseLocked)
        return;

    if (client->isFirstMouse) {
        client->lastMouseX = xpos;
        client->lastMouseY = ypos;
        client->isFirstMouse = false;
        return;
    }

    float xoffset = static_cast<float>(xpos - client->lastMouseX) * config::MOUSE_SENSITIVITY;
    float yoffset = static_cast<float>(ypos - client->lastMouseY) * config::MOUSE_SENSITIVITY;

    client->lastMouseX = xpos;
    client->lastMouseY = ypos;

    client->yaw += xoffset;
    client->pitch -= yoffset;

    if (client->pitch > config::MAX_PITCH) {
        client->pitch = config::MAX_PITCH;
    } else if (client->pitch < config::MIN_PITCH) {
        client->pitch = config::MIN_PITCH;
    }

    glm::vec3 cameraDir;
    cameraDir.x = cos(glm::radians(client->yaw)) * cos(glm::radians(client->pitch));
    cameraDir.y = sin(glm::radians(client->pitch));
    cameraDir.z = sin(glm::radians(client->yaw)) * cos(glm::radians(client->pitch));
    client->camera.setDirection(glm::normalize(cameraDir));
}

void keyCallback(GLFWwindow* window, int key, int, int action, int mods) {
    if (action == GLFW_PRESS) {
        Client* client = static_cast<Client*>(glfwGetWindowUserPointer(window));

        // Toggle mouse lock with Esc
        if (key == GLFW_KEY_ESCAPE) {
            client->isMouseLocked = !client->isMouseLocked;

            if (client->isMouseLocked) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                client->isFirstMouse = true;
            } else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }

        // Toggle bounding box mode with Shift + B
        if (key == GLFW_KEY_B && (mods & GLFW_MOD_SHIFT)) {
            client->boundingBoxMode = !client->boundingBoxMode;
        }
    }
}

static float directionToYaw(const glm::vec3& direction) {
    return glm::degrees(atan2(direction.z, direction.x));
}

static glm::vec3 yawToDirection(float yaw) {
    float rad = glm::radians(yaw);
    return glm::normalize(glm::vec3(cos(rad), 0.0f, sin(rad)));
}

Client::Client()
    : socket(std::make_unique<tcp::socket>(ioContext)), isMouseLocked(true), lastMouseX(0.0),
      lastMouseY(0.0), isFirstMouse(true), yaw(0.0f), pitch(0.0f), boundingBoxMode(false) {}

Client::~Client() {}

bool Client::init() {
    if (!connectToServer())
        return false;

    if (!audioManager.init()) {
        std::cerr << "Failed to initialize FMOD.\n";
        return 1;
    }

    audioManager.loadFMODStudioBank("../src/client/audioBanks/OutofTune/Build/Desktop/Master.bank");
    audioManager.loadFMODStudioBank("../src/client/audioBanks/OutofTune/Build/Desktop/BGM.bank");
    audioManager.loadFMODStudioBank("../src/client/audioBanks/OutofTune/Build/Desktop/SFX.bank");

    return true;
}

bool Client::connectToServer() {
    try {
        tcp::resolver resolver(ioContext);
        auto endpoints = resolver.resolve(config::SERVER_IP, std::to_string(config::SERVER_PORT));

        boost::asio::connect(*socket, endpoints);

        bool receivedId = false;

        while (!receivedId) {
            boost::asio::read_until(*socket, buffer, '\n');
            std::istream is(&buffer);
            std::string message;
            std::getline(is, message);

            if (message.empty())
                continue;

            json parsed = json::parse(message);
            std::string type = parsed.value("type", "");

            if (type == "join") {
                clientId = parsed["id"];
                receivedId = true;
                std::cout << "Received ID: " << clientId << "\n";
            }
        }

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return false;
    }
}

void Client::receiveServerMessage() {
    if (!socket || !socket->is_open())
        return;

    try {
        boost::asio::read_until(*socket, buffer, '\n');
        std::istream is(&buffer);
        std::string message;
        std::getline(is, message);

        if (!message.empty()) {
            handleServerMessage(message);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        exit(1);
    }
}

static glm::vec3 toVec3(json arr) {
    return glm::vec3(arr[0], arr[1], arr[2]);
}

void Client::handleServerMessage(const std::string& message) {
    json parsed = json::parse(message);
    std::string type = parsed.value("type", "");
    if (type == "player_states") {
        updatePlayerStates(parsed);
    } else if (type == "time_left") {
        updateGameTimer(parsed);
    } else if (type == "swamp_init") {
        int roomID = parsed["room_ID"];
        std::string audioFile = parsed["audio_file"];

        swamp = new Swamp(roomID, audioFile);
    } else if (type == "lilypad_drop") {
        auto id = parsed["id"];

        scene->removeInstanceFromRoom("swampRoom", "lilypad", id);
        scene->renderLilypadShadowPass(id);
    } else if (type == "cannonball_positions") {
        glm::vec3 positions[config::NUM_CANNONBALLS];
        const auto& cannonballs = parsed["cannonballs"];
        for (const auto& cannonball : cannonballs) {
            int id = cannonball["id"];
            glm::vec3 position = toVec3(cannonball["position"]);
            if (id >= 0 && id < config::NUM_CANNONBALLS) {
                positions[id] = position;
            }
        }
        scene->updateCannonballPositions(positions);
    } else if (type == "room_id") {
        auto roomID = parsed["id"];
        auto clientId = parsed["client_id"];

        scene->setPlayerRoomID(clientId, roomID);

        // Audio logic

        if (clientId == this->clientId) {
            if (ambianceId && ambianceId[0] != '\0') {
                audioManager.stopEvent(this->ambianceId);
            }

            if (roomID == 1) {
                // Swamp room
                this->ambianceId = config::SWAMP_AMBIENCE_TRACK;
                this->ambianceVol = config::SWAMP_AMBIENCE_VOL;

                this->footstepSfxId = config::FOOTSTEPWOOD;
                this->footstepVol = config::FOOTSTEPWOOD_VOL;

                audioManager.loadFMODStudioEvent(this->ambianceId);
                audioManager.playEvent(this->ambianceId);
                audioManager.setEventVolume(this->ambianceId, this->ambianceVol);
            } else if (roomID == 3) {
                // Carnival room
                this->ambianceId = config::CARNIVAL_AMBIENCE_TRACK;
                this->ambianceVol = config::CARNIVAL_AMBIENCE_VOL;

                this->footstepSfxId = config::FOOTSTEPWOOD;
                this->footstepVol = config::FOOTSTEPWOOD_VOL;

                audioManager.loadFMODStudioEvent(this->ambianceId);
                audioManager.playEvent(this->ambianceId);
                audioManager.setEventVolume(this->ambianceId, this->ambianceVol);
            } else if (roomID == 5) {
                // Piano room

                this->ambianceId = config::PIANO_AMBIENCE_TRACK;
                this->ambianceVol = config::PIANO_AMBIENCE_VOL;
                audioManager.loadFMODStudioEvent(this->ambianceId);
                audioManager.playEvent(this->ambianceId);

                this->footstepSfxId = config::FOOTSTEPWOOD;
                this->footstepVol = config::FOOTSTEPWOOD_VOL;
            } else {
                this->ambianceId = "";

                this->footstepSfxId = config::FOOTSTEPCARPET;
                this->footstepVol = config::FOOTSTEPCARPET_VOL;
            }
        }

    } else if (type == "sfx") {
        // JSON expected: {"type": "sfx", "sfx_id": "event:/SFX/footstep_carpet", "client_id": 0,
        // "action": "jump", "volume": 1.0f (optional), "stopID": "eventID" (optional)} client id
        // that of the person triggering the sfx

        std::string sfxIDStr = parsed["sfx_id"];
        const char* sfxID = sfxIDStr.c_str();
        int clientId = parsed["client_id"];
        std::string action = parsed["action"];
        float volume = parsed.value("volume", 1.0f);

        audioManager.stopEvent(sfxID); // Stop the event if it's already playing
        if (clientId == this->clientId) {
            audioManager.loadFMODStudioEvent(sfxID);
            audioManager.playEvent(sfxID);
            audioManager.setEventVolume(sfxID, volume);
        }

        if (action == "door_open") {
            auto doorID = parsed["door_id"];
            // TODO: remove rendering of door
        }

    } else if (type == "interactable_nearby") {
        scene->canvas->setInteractHidden(false);
    } else if (type == "interactable_not_nearby") {
        scene->canvas->setInteractHidden(true);
    } else if (type == "pause_circus_music") {
        audioManager.stopEvent("circus_music");
    } else if (type == "unpause_circus_music") {
        // TODO: handle the first loading of the circus music
        // - should hopefully be handled by Helen's code to get rooms to play their audio
        audioManager.playEvent("circus_music");
    } else if (type == "key_pickup") {
        auto keyID = parsed["keyID"];
        auto playerID = parsed["playerID"];
        auto roomName = parsed["room"];
        /*
        TODO: update remove key from room logic to use keyID instead of 0.
        NOTE: The current logic assumes that no room has more than one key.
        We use '0' instead of 'keyID' in `scene->removeInstanceFromRoom(roomName, "key", 0)`
        because in the scene, we go by room, so we are removing the only key in the room,
        meaning it has id 0. When creating keys in the scene for a given room, they are
        hardcoded as `SOME_ROOM->children["key"][0] = ...`. We aren't mapping them by id of all
        keys created. Thus, we have to remove 0 rather than keyID.
         */
        std::cout << "removing key " << keyID << " from room " << roomName << std::endl;
        scene->removeInstanceFromRoom(roomName, "key", 0);
        std::cout << "key " << keyID << " removed from room " << roomName << std::endl;
        if (playerID == this->clientId) {
            scene->canvas->collectKey();
        }

        // Assumes there's only one key in the room for now.
        // Will refactor if we add more interactable objects later.
        scene->setInteractableShadowActive(roomName, 0, false);
    } else if (type == "final_door_interact") {
        // Need to have some sort of animation or graphics where the key is added to the door
        int keySlot = parsed["slot_id"];
        auto roomName = parsed["room"];
        std::cout << "Checking keySlot and roomName" << roomName << keySlot << std::endl;
        std::cout << "interacted with final door" << roomName << keySlot << std::endl;

        scene->addKeyToSlot(roomName, "final_door_key", keySlot);
        scene->canvas->removeKey();

        // Make the key appear at the correct positions
        // Positions are set in the config file
    } else if (type == "final_door_open") {
        // This is the final door opening, so we need to update the scene
        // and show the end screen.
        scene->removeInstanceFromRoom("lobby", "finalDoor", 0);
    } else if (type == "final_button_pressed") {
        // Could just be sfx only
        int playerID = parsed["player_id"];
        scene->moveChildTransform("lobby", "final_button", playerID, glm::vec3(0.0f, 0.0f, -0.02f));

    } else {
        std::cerr << "Unknown message type: " << type << "\n";
    }
    // Need to also udpate object states
}

void Client::updatePlayerStates(const json& parsed) {
    const auto& players = parsed["players"];
    std::unordered_set<int> connectedIds;

    for (const auto& player : players) {
        int id = player["id"];
        connectedIds.insert(id);

        glm::vec3 position = toVec3(player["position"]);
        glm::vec3 direction = toVec3(player["direction"]);

        playerPositions[id] = position;
        playerDirections[id] = direction;

        scene->setPlayerState(id, player["state"]);

        if (id == clientId) {
            camera.setPosition(position + config::CAMERA_OFFSET);
        }
    }

    for (int i = 0; i < config::MAX_PLAYERS; ++i) {
        if (playerPositions.contains(i) && !connectedIds.contains(i)) {
            playerPositions.erase(i);
            playerDirections.erase(i);
            disconnectedIds.insert(i);
        }
    }
}

void Client::updateGameTimer(const json& parsed) {
    scene->canvas->updateTimer(parsed["minutes"], parsed["seconds"]);
}

static std::string mapKeyToAction(int key) {
    switch (key) {
    case GLFW_KEY_W:
    case GLFW_KEY_UP:
        return "move_forward";
    case GLFW_KEY_S:
    case GLFW_KEY_DOWN:
        return "move_backward";
    case GLFW_KEY_A:
    case GLFW_KEY_LEFT:
        return "strafe_left";
    case GLFW_KEY_D:
    case GLFW_KEY_RIGHT:
        return "strafe_right";
    case GLFW_KEY_SPACE:
        return "jump";
    case GLFW_KEY_E:
        return "interact";
    case GLFW_KEY_N:
        return "n";
    default:
        return "";
    }
}

void Client::handleKeyboardInput(GLFWwindow* window) {
    static const std::vector<int> keysToCheck = {
        GLFW_KEY_W, GLFW_KEY_UP,    GLFW_KEY_S,     GLFW_KEY_DOWN, GLFW_KEY_A, GLFW_KEY_LEFT,
        GLFW_KEY_D, GLFW_KEY_RIGHT, GLFW_KEY_SPACE, GLFW_KEY_E,    GLFW_KEY_N};

    json message;

    message["type"] = "keyboard_input";
    message["actions"] = json::array();

    for (const int& key : keysToCheck) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            std::string action = mapKeyToAction(key);

            if (!action.empty()) {
                message["actions"].push_back(action);
                if (action != "jump" && action != "interact") {
                    // This is footstep sfx

                    if (footstepCooldown == config::FOOTSTEP_COOLDOWN_RATE) {
                        audioManager.loadFMODStudioEvent(footstepSfxId);
                        audioManager.setEventVolume(footstepSfxId, footstepVol);
                        audioManager.playEvent(footstepSfxId);

                        footstepCooldown = 0;
                    }

                    footstepCooldown++;
                }
            }
        }
    }

    if (!message["actions"].empty()) {
        sendMessageToServer(message);
    }
}

void Client::handleMouseInput() {
    if (!isMouseLocked)
        return;

    glm::vec3 direction = yawToDirection(yaw);
    if (scene)
        scene->canvas->updateCompass(direction);
    json message;

    message["type"] = "mouse_input";
    message["direction"] = {direction.x, direction.y, direction.z};

    sendMessageToServer(message);
}

void Client::sendMessageToServer(const json& message) {
    std::string packet = message.dump() + "\n";
    boost::asio::write(*socket, boost::asio::buffer(packet));
}

bool Client::initWindow(GLFWwindow*& window) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW.\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(config::WORLD_WIDTH, config::WORLD_HEIGHT, "Out of Tune", nullptr,
                              nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        return false;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // lock & hide the cursor

    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    float aspect = static_cast<float>(width) / height;
    camera.setAspect(aspect);

    return true;
}

void Client::initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_PROGRAM_POINT_SIZE);
}

void Client::initScene() {
    scene = std::make_unique<Scene>(clientId);
    scene->init();

    glm::vec3 position = config::PLAYER_SPAWNS[clientId];
    glm::vec3 direction =
        glm::normalize(glm::vec3(-position.x, 0.0f, -position.z)); // will change this later

    camera.setPosition(position + config::CAMERA_OFFSET);
    camera.setDirection(direction);
    yaw = directionToYaw(direction);
}

void Client::gameLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.75f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        handleKeyboardInput(window);
        handleMouseInput();

        receiveServerMessage();

        for (const auto& [id, position] : playerPositions) {
            scene->updatePlayerState(id, position, playerDirections.at(id));
        }

        for (const int& id : disconnectedIds) {
            scene->removePlayer(id);
        }
        disconnectedIds.clear();

        scene->render(camera, boundingBoxMode);

        audioManager.update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Client::cleanup(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Client::run() {
    GLFWwindow* window = nullptr;

    if (!initWindow(window))
        return;

    initGL();
    initScene();
    scene->window = window;
    gameLoop(window);
    cleanup(window);
}
