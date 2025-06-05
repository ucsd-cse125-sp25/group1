#include "server.hpp"
#include <boost/system/error_code.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include "config.hpp"
#include "json.hpp"

using tcp = boost::asio::ip::tcp;
using json = nlohmann::ordered_json;
using Clock = std::chrono::steady_clock;

Server::Server()
    : acceptor(ioContext, tcp::endpoint(tcp::v4(), config::SERVER_PORT)), tickTimer(ioContext),
      gameTimer(ioContext), hasTimerStarted(false), timeLeft(config::TOTAL_GAME_TIME) {}

Server::~Server() {
    delete swamp;
}

static vec3 toVec3(const json& arr) {
    return vec3(arr[0], arr[1], arr[2]);
}

void Server::initRigidBodies() {
    std::ifstream inLayout("../src/server/data/layout.json");
    std::ifstream inDimensions("../src/server/data/dimensions.json");
    json layout, dimensions;
    inLayout >> layout;
    inDimensions >> dimensions;

    for (auto it = layout.begin(); it != layout.end(); ++it) {
        const std::string& roomName = it.key();
        cout << "Initializing room " << roomName << " with ID " << rooms.size() << endl;
        Room* room;
        if (roomName == "swampRoom") {
            swamp = new Swamp(rooms.size(), world, *this);
            room = static_cast<Room*>(swamp);
        } else {
            room = new Room(rooms.size(), roomName);
        }
        rooms[rooms.size()] = room;
    }

    // for (const auto& room : layout) {
    int i = 0;
    for (auto it = layout.begin(); it != layout.end(); ++it) {
        const std::string& roomName = it.key();
        const json& room = it.value();
        cout << "Initializing room: " << roomName << endl;
        vec3 roomPosition = toVec3(room["position"]);

        for (const auto& obj : room["objects"]) {
            string modelName = obj["model"];
            // std::cout << modelName << std::endl;
            vec3 position = toVec3(obj["position"]);
            vec3 minCorner = toVec3(dimensions[modelName]["min"]);
            vec3 maxCorner = toVec3(dimensions[modelName]["max"]);

            bool isRotated = obj["rotated"];
            if (isRotated) {
                minCorner = vec3(minCorner.z, minCorner.y, minCorner.x);
                maxCorner = vec3(maxCorner.z, maxCorner.y, maxCorner.x);
            }

            vec3 relativePosition =
                (toVec3(dimensions[modelName]["max"]) + toVec3(dimensions[modelName]["min"])) *
                0.5f;

            vec3 relativeMinCorner = minCorner - relativePosition;
            vec3 relativeMaxCorner = maxCorner - relativePosition;

            RigidBody* object = nullptr;

            TransformData data = {roomPosition, position, relativePosition, relativeMinCorner,
                                  relativeMaxCorner};

            if (modelName == "door_00") {
                object = initDoor(data, &doors, &rooms, &world, *this, i, obj["connects_to"], -1);
            } else if (modelName == "frog_00") {
                object = initFrog(data, &objects, swamp, &world);
            } else if (modelName == "lilypad_00") {
                object = initLilyPad(data, swamp, &world);
            } else if (modelName == "water_00") {
                object = initWater(data, swamp, &world);
            } else if (modelName == "water_01") {
                object = initSplash(data, swamp, &world);
            } else if (modelName == "key_00") {
                object = initKey(data, *this, world, roomName, &keys);
            } else if (modelName.starts_with("zone_")) {
                object = initZone(data, this, &objects, &world, i);
            } else {
                if (modelName == "bypass_00" && !config::BYPASS)
                    continue;
                object = initObject(data, &objects, &world);
            }

            world.addObject(object);
        }
        i++;
    }
}

bool Server::init() {
    std::cout << "IP Address: " << config::SERVER_IP << "\nPort: " << config::SERVER_PORT << "\n";

    initRigidBodies();

    return true;
}

int Server::findAvailableId() {
    for (int i = 0; i < config::MAX_PLAYERS; ++i) {
        if (!clients.contains(i))
            return i;
    }
    return -1;
}

void Server::acceptConnections() {
    auto socket = std::make_shared<tcp::socket>(ioContext);

    acceptor.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        acceptConnections();

        if (!ec) {
            int clientId = findAvailableId();

            if (clientId != -1) {
                clients[clientId] = socket;
                std::cout << "Client #" << clientId << " connected.\n";

                handleClientJoin(clientId);
                listenToClient(clientId);
            } else {
                std::cout << "Server is full. Connection rejected.\n";
            }
        } else {
            std::cerr << "Failed to connect: " << ec.message() << "\n";
        }
    });
}

void Server::handleClientJoin(int clientId) {
    auto socket = clients[clientId];

    json message;
    message["type"] = "join";
    message["id"] = clientId;

    std::string packet = message.dump() + "\n";
    boost::asio::write(*socket, boost::asio::buffer(packet));

    // Send over the swamp init info
    std::string swampPacket = swamp->getInitInfo();
    boost::asio::write(*socket, boost::asio::buffer(swampPacket));

    glm::vec3 position = config::PLAYER_SPAWNS[clientId];
    glm::vec3 direction =
        glm::normalize(glm::vec3(-position.x, 0.0f, -position.z)); // will change this later
    Player* player = new Player(clientId, 0, position, direction, &world);
    players[clientId] = player;

    // Temporary:
    player->setCurRoomID(0); // Set the player's current room to Swamp

    // add player to physics world
    world.addObject(&(player->getBody()));

    if (!hasTimerStarted && clients.size() == 4) {
        hasTimerStarted = true;
        startGameTimer();
    }
}

void Server::handleClientDisconnect(int clientId) {
    auto it = clients.find(clientId);

    if (it != clients.end()) {
        it->second->close();
        clients.erase(it);

        buffers.erase(clientId);
        clientMessages.erase(clientId);

        world.removeObject(&players[clientId]->getBody());
        delete players[clientId];
        players.erase(clientId);

        std::cout << "Client #" << clientId << " disconnected.\n";
    }

    if (hasTimerStarted && clients.size() == 0) {
        hasTimerStarted = false;
        gameTimer.cancel();
        timeLeft = config::TOTAL_GAME_TIME;
    }
}

void Server::listenToClient(int clientId) {
    auto socket = clients[clientId];

    boost::asio::async_read_until(
        *socket, buffers[clientId], '\n',
        [this, clientId](const boost::system::error_code& ec, std::size_t) {
            if (!ec) {
                std::string message;

                if (!clients.contains(clientId))
                    return;

                std::istream is(&buffers[clientId]);
                std::getline(is, message);

                if (!message.empty()) {
                    clientMessages[clientId].push_back(message);
                }

                listenToClient(clientId);
            } else {
                handleClientDisconnect(clientId);
            }
        });
}

void Server::startTick() {
    tickTimer.expires_after(std::chrono::milliseconds(config::TICK_RATE));
    tickTimer.async_wait([this](const boost::system::error_code& ec) {
        if (!ec) {
            handleClientMessages();
            handlePhysics();
            broadcastPlayerStates();

            startTick();
        }
    });
}

static glm::vec3 toGlmVec3(const json& arr) {
    return glm::vec3(arr[0], arr[1], arr[2]);
}

void Server::handleClientMessages() {
    for (auto& [clientId, messages] : clientMessages) {
        for (const auto& message : messages) { // process all the messages
            json parsed = json::parse(message);
            std::string type = parsed.value("type", "");

            if (type == "keyboard_input") {
                const std::vector<std::string> actions =
                    parsed["actions"].get<std::vector<std::string>>();

                // handle WASD and jump inputs
                players[clientId]->handleMovementInput(actions);

                int roomID = players[clientId]->getCurRoomID();
                Interactable* interactable =
                    players[clientId]->getNearestInteractable(rooms[roomID]);

                // if an interactable is nearby, notify user on the client
                if (interactable != nullptr) {
                    if (interactableTracked == nullptr ||
                        interactable->getID() != interactableTracked->getID()) {
                        json interactableMessage;
                        interactableMessage["type"] = "interactable_nearby";
                        interactableMessage["id"] = interactable->getID();

                        std::string packet = interactableMessage.dump() + "\n";

                        interactableTracked = interactable;
                        try {
                            boost::asio::write(*clients[clientId], boost::asio::buffer(packet));
                        } catch (const std::exception& e) {
                            handleClientDisconnect(clientId);
                            continue; // skip further processing for this client
                        }
                    }
                } else {
                    if (interactableTracked != nullptr) {

                        json interactableMessage;
                        interactableMessage["type"] = "interactable_not_nearby";

                        std::string packet = interactableMessage.dump() + "\n";

                        interactableTracked = nullptr;
                        try {
                            boost::asio::write(*clients[clientId], boost::asio::buffer(packet));
                        } catch (const std::exception& e) {
                            handleClientDisconnect(clientId);
                            continue; // skip further processing for this client
                        }
                    }
                }
                // handle misc inputs, such as interacting with environment
                players[clientId]->handleGeneralInput(actions, interactable);
            } else if (type == "mouse_input") {
                glm::vec3 direction = toGlmVec3(parsed["direction"]);
                players[clientId]->handleMouseInput(direction);
            }
        }

        messages.clear();
    }
}

void Server::handlePhysics() {
    world.step(config::TICK_RATE * 0.001);
    world.resolveCollisions();
}

void Server::broadcastPlayerStates() {
    for (const auto& [clientId, socket] : clients) {
        json message;
        message["type"] = "player_states";

        for (const auto& [id, player] : players) {
            vec3 position = player->getBody().getPosition();
            vec3 direction = player->getBody().getDirection();
            // WARNING: Completely deletes all horizontal motion
            player->getBody().setVelocity(vec3(0.0f, player->getBody().getVelocity().y, 0.0f));

            json entry;
            entry["id"] = id;
            entry["position"] = {position.x, position.y, position.z};
            entry["direction"] = {direction.x, direction.y, direction.z};

            message["players"].push_back(entry);
        }

        std::string packet = message.dump() + "\n";

        try {
            boost::asio::write(*socket, boost::asio::buffer(packet));
        } catch (const std::exception& e) {
            handleClientDisconnect(clientId);
        }
    }
}

void Server::startGameTimer() {
    gameTimer.expires_after(std::chrono::seconds(1));
    gameTimer.async_wait([this](const boost::system::error_code& ec) {
        if (!ec) {
            broadcastTimeLeft();
            startGameTimer();
        } else if (ec == boost::asio::error::operation_aborted) {
            return;
        }
    });
}

void Server::broadcastTimeLeft() {
    json message;
    message["type"] = "time_left";
    message["minutes"] = timeLeft / 60;
    message["seconds"] = timeLeft % 60;
    std::string packet = message.dump() + "\n";

    for (const auto& [clientId, socket] : clients) {
        try {
            boost::asio::write(*socket, boost::asio::buffer(packet));
        } catch (const std::exception& e) {
            handleClientDisconnect(clientId);
        }
    }

    if (timeLeft > 0) {
        --timeLeft;
    }
}

void Server::broadcastMessage(std::string packet) {

    for (const auto& [clientId, socket] : clients) {
        try {
            boost::asio::write(*socket, boost::asio::buffer(packet));
        } catch (const std::exception& e) {
            handleClientDisconnect(clientId);
        }
    }
}

void Server::run() {
    std::cout << "Server is running...\n";

    acceptConnections();
    startTick();

    try {
        ioContext.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
