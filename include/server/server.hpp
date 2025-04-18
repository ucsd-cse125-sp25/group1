#pragma once

#include <boost/asio.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>

enum class PlayerState {
    Connected,
    Ready,
    Playing,
    Disconnected
};

class Server {
public:
    Server();
    ~Server();

    bool init();
    void run();

private:
    int findAvailableId();
    void acceptConnections();
    void handleClient(std::shared_ptr<boost::asio::ip::tcp::socket> socket, int clientId);
    void handleClientDisconnect(int clientId);

    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::acceptor acceptor;

    std::unordered_map<int, std::shared_ptr<boost::asio::ip::tcp::socket>> clients;
    std::unordered_map<int, PlayerState> playerStates;
    std::unordered_map<int, glm::vec3> playerPositions;
};
