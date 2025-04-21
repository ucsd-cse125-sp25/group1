#include "scene.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Scene::Scene() {}
Scene::~Scene() {}

void Scene::init(int clientId) {
    shader = std::make_unique<Shader>(
        "../src/client/shaders/basic.vert",
        "../src/client/shaders/basic.frag"
    );
    
    floor = std::make_unique<Cube>();
}

void Scene::updatePlayerState(int id, const glm::vec3& position, const glm::vec3& direction) {
    if (!players.contains(id)) {
        players.emplace(id, Player(id, position, direction));
    } else {
        players.at(id).position = position;
        players.at(id).direction = direction;
    }
}

void Scene::removePlayer(int id) {
    players.erase(id);
}

void Scene::render(const Camera& camera) {
    shader->use();

    shader->setMat4("view", camera.getViewMatrix());
    shader->setMat4("projection", camera.getProjectionMatrix());
    shader->setVec3("color", glm::vec3(0.75f, 0.9f, 0.75f));

    glm::mat4 floorModel = glm::mat4(1.0f);
    floorModel = glm::translate(floorModel, glm::vec3(0.0f, -0.5f, 0.0f));
    floorModel = glm::scale(floorModel, glm::vec3(20.0f, 1.0f, 20.0f));
    shader->setMat4("model", floorModel);
    floor->draw();

    for (auto& [id, player] : players) {
        player.draw(*shader);
    }
}
