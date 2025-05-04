#include "scene.hpp"
#include <array>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Scene::Scene() {}
Scene::~Scene() {}

void Scene::init() {
    shader = std::make_unique<Shader>(
        "../src/client/shaders/basic.vert",
        "../src/client/shaders/basic.frag"
    );
    
    modelShader = std::make_unique<Shader>(
        "../src/client/shaders/model.vert",
        "../src/client/shaders/model.frag"
    );

    room = std::make_unique<Model>("../src/client/models/1x1_hotel_room.obj");
    table = std::make_unique<Model>("../src/client/models/table.obj");
    door = std::make_unique<Model>("../src/client/models/door.obj");

    initRooms();
}

void Scene::initRooms() {
    const glm::mat4 I4{1.0f};   // 4 x 4 identity matrix 

    ModelInstance room1(room.get(), I4);
    modelInstances.emplace_back(std::move(room1));      // Move room into the model instance list
    ModelInstance& room1Ref = modelInstances.back();    // Reference the stored instance

    room1Ref.children.emplace_back(table.get(), I4, &room1Ref);

    std::array<float, 4> degrees = { 0.0f, 90.0f, 180.0f, 270.0f };

    for (int i = 0; i < 4; ++i) {
        glm::mat4 doorModel = glm::rotate(I4, glm::radians(degrees[i]), glm::vec3(0.0f, 1.0f, 0.0f));
        doorModel = glm::translate(doorModel, glm::vec3(10.0f, 0.0f, 0.0f));
        room1Ref.children.emplace_back(door.get(), doorModel, &room1Ref);
    }
}

void Scene::updatePlayerState(int id, const glm::vec3& position, const glm::vec3& direction) {
    if (!players.contains(id)) {
        players.emplace(id, Player(id, position, direction));
    } else {
        players.at(id).setPosition(position);
        players.at(id).setDirection(direction);
    }
}

void Scene::removePlayer(int id) {
    players.erase(id);
}

void Scene::render(const Camera& camera) {
    modelShader->use();

    modelShader->setMat4("view", camera.getViewMatrix());
    modelShader->setMat4("projection", camera.getProjectionMatrix());

    // Draw all model instances in the scene
    for (const auto& instance : modelInstances) {
        instance.drawRecursive(*modelShader);
    }

    shader->use();

    shader->setMat4("view", camera.getViewMatrix());
    shader->setMat4("projection", camera.getProjectionMatrix());

    for (auto& [id, player] : players) {
        player.draw(*shader);
    }
}
