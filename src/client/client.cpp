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
        std::string line;
        std::getline(is, line);

        clientId = std::stoi(line);

        std::cout << "Received ID: " << clientId << "\n";

        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return false;
    }
}

bool Client::init() {
    if (!connectToServer()) return false;

    glm::vec3 cameraPos = config::PLAYER_SPAWNS[clientId] + config::CAMERA_OFFSET;
    camera.emplace(cameraPos);

    return true;
}

void Client::render() {
    shader->use();

    shader->setMat4("view", camera->getViewMatrix());
    shader->setMat4("projection", camera->getProjectionMatrix());

    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", model);
    cube->draw();
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

    shader = std::make_unique<Shader>(
        "../src/client/shaders/basic.vert",
        "../src/client/shaders/basic.frag"
    );
    
    cube = std::make_unique<Cube>();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
