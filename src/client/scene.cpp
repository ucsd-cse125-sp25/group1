#include "scene.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <glad/glad.h>
#include <iostream>

struct PointLight {
    glm::vec3 position;
    glm::vec3 color;
};

Scene::Scene() {}
Scene::~Scene() {}

void Scene::init() {
    shader = std::make_unique<Shader>("../src/client/shaders/basic.vert",
                                      "../src/client/shaders/basic.frag");

    modelShader = std::make_unique<Shader>("../src/client/shaders/model.vert",
                                           "../src/client/shaders/model.frag");

    uiShader =
        std::make_unique<Shader>("../src/client/shaders/ui.vert", "../src/client/shaders/ui.frag");

    room = std::make_unique<Model>("../src/client/models/1x1_hotel_room.obj");
    table = std::make_unique<Model>("../src/client/models/table.obj");

    timer = std::make_unique<TimerDisplay>();

    door = std::make_unique<Model>("../src/client/models/door.obj");

    initRooms();
}

void Scene::initRooms() {
    const glm::mat4 I4{1.0f}; // 4 x 4 identity matrix

    // Create first room
    auto room1 = std::make_unique<ModelInstance>(room.get(), I4);
    ModelInstance* room1Ptr = room1.get();

    room1->children["table"][0] = std::make_unique<ModelInstance>(table.get(), I4, room1Ptr);

    std::array<float, 4> degrees = {0.0f, 90.0f, 180.0f, 270.0f};

    for (int i = 0; i < 4; ++i) {
        glm::mat4 doorModel =
            glm::rotate(I4, glm::radians(degrees[i]), glm::vec3(0.0f, 1.0f, 0.0f));
        doorModel = glm::translate(doorModel, glm::vec3(10.0f, 0.0f, 0.0f));
        room1->children["door"][i] =
            std::make_unique<ModelInstance>(door.get(), doorModel, room1Ptr);
    }

    modelInstances["room1"] = std::move(room1);
}

void Scene::updatePlayerState(int id, const glm::vec3& position, const glm::vec3& direction) {
    if (!players.contains(id)) {
        players.emplace(id, Player(id, position, direction));
    } else {
        players.at(id).setPosition(position);
        players.at(id).setDirection(direction);
    }
}

void Scene::updateTimer(int minutes, int seconds) {
    timer->updateTimer(minutes, seconds);
    // int lMinutes = minutes / 10;
    // int rMinutes = minutes % 10;

    // int lSeconds = seconds / 10;
    // int rSeconds = seconds % 10;
    // std::cout << lMinutes << rMinutes << ":" << lSeconds << rSeconds << std::endl;
}

void Scene::removePlayer(int id) {
    players.erase(id);
}

void Scene::removeInstanceFromRoom(const std::string& roomName, const std::string& type, int id) {
    modelInstances[roomName]->deleteChild(type, id);
}

void Scene::render(const Camera& camera, bool boundingBoxMode) {
    modelShader->use();

    modelShader->setMat4("view", camera.getViewMatrix());
    modelShader->setMat4("projection", camera.getProjectionMatrix());
    modelShader->setVec3("viewPos", camera.getPosition());

    // This is for testing, will change this later
    std::vector<PointLight> testLights = {
        {glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f)},
    };

    // This is for testing, will change this later
    modelShader->setInt("numLights", testLights.size());
    for (int i = 0; i < testLights.size(); ++i) {
        modelShader->setVec3("pointLights[" + std::to_string(i) + "].position",
                             testLights[i].position);
        modelShader->setVec3("pointLights[" + std::to_string(i) + "].color", testLights[i].color);
    }

    // Draw all model instances in the scene
    for (const auto& [name, instance] : modelInstances) {
        instance->drawRecursive(*modelShader, boundingBoxMode);
    }

    shader->use();

    shader->setMat4("view", camera.getViewMatrix());
    shader->setMat4("projection", camera.getProjectionMatrix());

    for (auto& [id, player] : players) {
        player.draw(*shader, boundingBoxMode);
    }

    // UI
    timer->draw(*uiShader);
}
