#pragma once

#include <boost/asio.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include <unordered_set>
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

    Camera camera;

private:
    bool connectToServer();

    void receiveServerMessage();
    void handleServerMessage(std::string message);

    void handlePlayerInput(GLFWwindow* window);
    void sendMessageToServer(const nlohmann::json& message);

    bool initWindow(GLFWwindow*& window);
    void initGL();
    void initScene();
    void gameLoop(GLFWwindow* window);
    void cleanup(GLFWwindow* window);

    boost::asio::io_context ioContext;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;

    boost::asio::streambuf buffer;

    int clientId;

    std::unordered_map<int, glm::vec3> playerPositions;
    std::unordered_map<int, glm::vec3> playerDirections;

    std::unordered_set<int> disconnectedIds;

    std::unique_ptr<Scene> scene;
};
