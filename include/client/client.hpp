#pragma once

#include <boost/asio.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include "json.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "scene.hpp"
#include "shader.hpp"

class Client {
public:
    Client();
    ~Client();

    bool init();
    void run();

private:
    bool connectToServer();

    void receiveServerMessage();
    void handleServerMessage(std::string message);

    void sendMessageToServer(const nlohmann::json& message);

    boost::asio::io_context ioContext;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;

    int clientId;

    std::unordered_map<int, glm::vec3> playerPositions;

    std::unique_ptr<Scene> scene;
};
