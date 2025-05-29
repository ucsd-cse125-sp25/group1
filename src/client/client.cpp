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

    // To play audio, first load in the name of the event, then play the event. Can use
    // setEventVolume to adjust the volume

    audioManager.loadFMODStudioEvent(config::SWAMP_AMBIENCE_TRACK);
    audioManager.playEvent(config::SWAMP_AMBIENCE_TRACK);
    audioManager.setEventVolume(config::SWAMP_AMBIENCE_TRACK, 1.0f);

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
    std::cout << "parsed is: " << parsed << std::endl;
    std::cout << "parsed[type] is: " << parsed["type"] << std::endl;
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
    } else if (type == "key_pickup") {
        std::cout << "In key_pickup if!" << std::endl;
        auto id = parsed["id"];
        std::cout << "id is" << id << std::endl;
        auto roomName = parsed["room"];
        std::cout << "roomName is " << roomName << std::endl;
        scene->removeInstanceFromRoom(roomName, "key", id);
        std::cout << "key removed successfully! " << std::endl;
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
    scene->updateTimer(parsed["minutes"], parsed["seconds"]);
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
    default:
        return "";
    }
}

void Client::handleKeyboardInput(GLFWwindow* window) {
    static const std::vector<int> keysToCheck = {
        GLFW_KEY_W,    GLFW_KEY_UP, GLFW_KEY_S,     GLFW_KEY_DOWN,  GLFW_KEY_A,
        GLFW_KEY_LEFT, GLFW_KEY_D,  GLFW_KEY_RIGHT, GLFW_KEY_SPACE, GLFW_KEY_E};

    json message;

    message["type"] = "keyboard_input";
    message["actions"] = json::array();

    for (const int& key : keysToCheck) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            std::string action = mapKeyToAction(key);

            if (!action.empty()) {
                message["actions"].push_back(action);
                if (action != "jump" && !audioManager.eventIsPlaying(config::footstepCarpet)) {
                    // This is footstep sfx
                    audioManager.loadFMODStudioEvent(config::footstepCarpet);
                    audioManager.setEventVolume(config::footstepCarpet, 0.1f);
                    audioManager.playEvent(config::footstepCarpet);
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
        scene->updateCompass(direction);
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
}

void Client::initScene() {
    scene = std::make_unique<Scene>();
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
