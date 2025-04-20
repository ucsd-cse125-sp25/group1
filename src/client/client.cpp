#include "client.hpp"
#include "config.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using boost::asio::ip::tcp;
using json = nlohmann::json;

Client::Client() : socket(std::make_unique<tcp::socket>(ioContext)) {}

Client::~Client() {}

bool Client::connectToServer() {
    try {
        tcp::resolver resolver(ioContext);
        auto endpoints = resolver.resolve(config::SERVER_IP, std::to_string(config::SERVER_PORT));

        boost::asio::connect(*socket, endpoints);

        boost::asio::streambuf buf;
        boost::asio::read_until(*socket, buf, '\n');
        std::istream is(&buf);
        std::string message;
        std::getline(is, message);

        clientId = std::stoi(message);

        std::cout << "Received ID: " << clientId << "\n";

        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return false;
    }
}

bool Client::init() {
    if (!connectToServer()) return false;

    return true;
}

void Client::receiveServerMessage() {
    if (!socket || !socket->is_open()) return;

    try {
        if (socket->available() > 0) {
            boost::asio::streambuf buf;
            boost::asio::read_until(*socket, buf, '\n');
            std::istream is(&buf);
            std::string message;
            std::getline(is, message);

            if (!message.empty()) {
                handleServerMessage(message);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void Client::handleServerMessage(std::string message) {
    json serverMsg = json::parse(message);
    std::string type = serverMsg.value("type", "");

    if (type == "player_positions") {
        const auto& players = serverMsg["players"];

        for (const auto& player : players) {
            int id = player["id"];
            json posArr = player["position"];
            glm::vec3 position = glm::vec3(posArr[0], posArr[1], posArr[2]);

            playerPositions[id] = position;
        }
    }
}

void Client::run() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW.\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        config::WORLD_WIDTH,
        config::WORLD_HEIGHT,
        "Out of Tune",
        nullptr,
        nullptr
    );

    if (!window) {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    scene = std::make_unique<Scene>();
    scene->init(clientId);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.75f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        receiveServerMessage();

        for (const auto& [id, position] : playerPositions) {
            scene->updatePlayerPosition(id, position);
        }

        scene->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
