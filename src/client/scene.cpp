#include "scene.hpp"
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
    modelShader->use();

    modelShader->setMat4("view", camera.getViewMatrix());
    modelShader->setMat4("projection", camera.getProjectionMatrix());

    glm::mat4 roomModel = glm::mat4(1.0f);
    modelShader->setMat4("model", roomModel);
    room->draw(*modelShader);

    glm::mat4 tableModel = glm::mat4(1.0f);
    modelShader->setMat4("model", tableModel);
    table->draw(*modelShader);

    shader->use();

    shader->setMat4("view", camera.getViewMatrix());
    shader->setMat4("projection", camera.getProjectionMatrix());

    for (auto& [id, player] : players) {
        player.draw(*shader);
    }
}
