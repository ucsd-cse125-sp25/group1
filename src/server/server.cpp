#include "server.hpp"
#include "config.hpp"
#include "json.hpp"
#include <boost/system/error_code.hpp>
#include <iostream>
#include <chrono>
#include <thread>

using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;
using Clock = std::chrono::steady_clock;

Server::Server() : acceptor(ioContext, tcp::endpoint(tcp::v4(), config::SERVER_PORT)) {}

Server::~Server() {}

bool Server::init() {
    std::cout << "IP Address: " << config::SERVER_IP << "\nPort: " << config::SERVER_PORT << "\n";
    return true;
}

int Server::findAvailableId() {
    for (int i = 0; i < config::MAX_PLAYERS; ++i) {
        if (!clients.contains(i)) return i;
    }
    return -1;
}

void Server::acceptConnections() {
    auto socket = std::make_shared<tcp::socket>(ioContext);

    acceptor.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        acceptConnections();

        if (!ec) {
            std::lock_guard<std::mutex> lock(mutex);

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

    glm::vec3 position = config::PLAYER_SPAWNS[clientId];
    playerPositions[clientId] = position;

    glm::vec3 direction = glm::normalize(glm::vec3(-position.x, 0.0f, -position.z)); // will change this later
    playerDirections[clientId] = direction;
}

void Server::handleClientDisconnect(int clientId) {
    std::lock_guard<std::mutex> lock(mutex);
    
    auto it = clients.find(clientId);

    if (it != clients.end()) {
        it->second->close();
        clients.erase(it);
        
        playerPositions.erase(clientId);
        playerDirections.erase(clientId);
        
        buffers.erase(clientId);
        clientMessages.erase(clientId);

        std::cout << "Client #" << clientId << " disconnected.\n";
    }
}

void Server::listenToClient(int clientId) {
    auto socket = clients[clientId];

    boost::asio::async_read_until(
        *socket,
        buffers[clientId],
        '\n',
        [this, clientId](const boost::system::error_code& ec, std::size_t) {
            if (!ec) {
                std::string message;

                {
                    std::lock_guard<std::mutex> lock(mutex);

                    if (!clients.contains(clientId)) return;

                    std::istream is(&buffers[clientId]);
                    std::getline(is, message);

                    if (!message.empty()) {
                        clientMessages[clientId].push_back(message);
                    }
                }

                listenToClient(clientId);
            } else {
                handleClientDisconnect(clientId);
            }
        }
    );
}

void Server::handleClientMessages() {
    std::lock_guard<std::mutex> lock(mutex);

    for (auto& [clientId, messages] : clientMessages) {
        if (!messages.empty()) {
            std::string message = messages.front();
            messages.pop_front();

            json parsed = json::parse(message);
            std::string type = parsed.value("type", "");

            if (type == "input") {
                const auto& actions = parsed["actions"];

                glm::vec3 direction = playerDirections[clientId];
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
                glm::vec3 right = glm::normalize(glm::cross(direction, up));

                for (const std::string& action : actions) {
                    if (action == "move_forward") {
                        playerPositions[clientId] += direction * config::PLAYER_SPEED;
                    } else if (action == "move_backward") {
                        playerPositions[clientId] -= direction * config::PLAYER_SPEED;
                    } else if (action == "strafe_left") {
                        playerPositions[clientId] -= right * config::PLAYER_SPEED;
                    } else if (action == "strafe_right") {
                        playerPositions[clientId] += right * config::PLAYER_SPEED;
                    }
                }
            }
        }
    }
}

void Server::broadcastPlayerStates() {
    std::lock_guard<std::mutex> lock(mutex);

    for (const auto& [clientId, socket] : clients) {
        json message;
        message["type"] = "player_states";

        for (const auto& [id, position] : playerPositions) {
            const auto& direction = playerDirections.at(id);

            json entry;
            entry["id"] = id;
            entry["position"] = { position.x, position.y, position.z };
            entry["direction"] = { direction.x, direction.y, direction.z };

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

void Server::run() {
    std::cout << "Server is running...\n";

    acceptConnections();

    std::thread([this]() {
        while (true) {
            auto start = Clock::now();

            handleClientMessages();
            broadcastPlayerStates();

            auto end = Clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            int waitTime = config::TICK_RATE - elapsed;

            if (waitTime > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
            }
        }
    }).detach();

    try {
        ioContext.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
