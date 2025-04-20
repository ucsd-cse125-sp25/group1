#include "server.hpp"
#include "config.hpp"
#include "json.hpp"
#include <iostream>
#include <boost/system/error_code.hpp>

using boost::asio::ip::tcp;
using json = nlohmann::json;

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
            int clientId = findAvailableId();

            if (clientId != -1) {
                clients[clientId] = socket;
                std::cout << "Client #" << clientId << " connected.\n";
                
                handleClient(socket, clientId);
                
                playerPositions[clientId] = config::PLAYER_SPAWNS[clientId];
                broadcastPlayerPositions();
            } else {
                std::cout << "Server is full. Connection rejected.\n";
            }
        } else {
            std::cerr << "Failed to connect: " << ec.message() << "\n";
        }
    });
}

void Server::handleClient(std::shared_ptr<tcp::socket> socket, int clientId) {
    boost::asio::write(*socket, boost::asio::buffer(std::to_string(clientId) + "\n"));
}

void Server::broadcastPlayerPositions() {
    for (const auto& [clientId, socket] : clients) {
        json playerPositionsMsg;

        playerPositionsMsg["type"] = "player_positions";

        for (const auto& [id, position] : playerPositions) {
            json entry;
            entry["id"] = id;
            entry["position"] = { position.x, position.y, position.z };

            playerPositionsMsg["players"].push_back(entry);
        }

        std::string message = playerPositionsMsg.dump() + "\n";
        boost::asio::write(*socket, boost::asio::buffer(message));
    }
}

void Server::handleClientDisconnect(int clientId) {
    auto it = clients.find(clientId);

    if (it != clients.end()) {
        it->second->close();
        clients.erase(it);
    }

    std::cout << "Client #" << clientId << " disconnected.\n";
}

void Server::run() {
    std::cout << "Server is running...\n";

    acceptConnections();

    try {
        ioContext.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
