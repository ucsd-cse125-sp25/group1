#pragma once

#include <boost/asio.hpp>
#include <deque>
#include <glm/glm.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>

class Server {
public:
    Server();
    ~Server();

    bool init();
    void run();

private:
    int findAvailableId();
    void acceptConnections();
    void handleClientJoin(int clientId);
    void handleClientDisconnect(int clientId);

    void listenToClient(int clientId);
    void handleClientMessages();

    void broadcastPlayerStates();

    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::acceptor acceptor;

    std::mutex mutex;

    std::unordered_map<int, std::shared_ptr<boost::asio::ip::tcp::socket>> clients;
    std::unordered_map<int, boost::asio::streambuf> buffers;

    std::unordered_map<int, glm::vec3> playerPositions;
    std::unordered_map<int, glm::vec3> playerDirections;

    std::unordered_map<int, std::deque<std::string>> clientMessages;
};
