#pragma once

#include <boost/asio.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include "json.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "shader.hpp"

class Client {
public:
    Client();
    ~Client();

    bool init();
    void run();

private:
    bool connectToServer();

    void render();

    void handleServerMessage();
    void sendMessageToServer(const nlohmann::json& message);

    void processInput();
    void updateOtherPlayers();

    void spawnPlayer(int id, const glm::vec3& pos);

    boost::asio::io_context ioContext;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;

    int clientId;

    glm::vec3 position;
    glm::vec3 velocity;

    std::unordered_map<int, glm::vec3> otherPlayers;

    std::unique_ptr<Cube> cube;

    std::optional<Camera> camera;
    std::unique_ptr<Shader> shader;
};
