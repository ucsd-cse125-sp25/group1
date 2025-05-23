#include "scene.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <cmath>
#include <glad/glad.h>
#include <iostream>
#include <vector>

struct PointLight {
    glm::vec3 position;
    glm::vec3 color;
};

Scene::Scene() {}
Scene::~Scene() {}

void Scene::init() {
    shader = std::make_unique<Shader>("../src/client/shaders/basic.vert",
                                      "../src/client/shaders/basic.frag");

    shaders["model"] = std::make_unique<Shader>("../src/client/shaders/model.vert",
                                                "../src/client/shaders/model.frag");

    shaders["swamp"] = std::make_unique<Shader>("../src/client/shaders/model.vert",
                                                "../src/client/shaders/swamp.frag");

    uiShader =
        std::make_unique<Shader>("../src/client/shaders/ui.vert", "../src/client/shaders/ui.frag");

    hotelRoomAsset = std::make_unique<Model>("../src/client/models/1x1_hotel_room.obj");
    tableAsset = std::make_unique<Model>("../src/client/models/table.obj");
    doorAsset = std::make_unique<Model>("../src/client/models/door.obj");

    swampRoomAsset = std::make_unique<Model>("../src/client/models/swamp_room.obj");
    lilypadAsset = std::make_unique<Model>("../src/client/models/lilypad.obj");

    timer = std::make_unique<TimerDisplay>();

    initRooms();
}

void Scene::initRooms() {
    const glm::mat4 I4{1.0f}; // 4 x 4 identity matrix

    // Hotel room
    glm::mat4 hotelRoomModel = glm::translate(I4, config::HOTEL_ROOM_POSITION);
    auto hotelRoom = std::make_unique<ModelInstance>(hotelRoomAsset.get(), hotelRoomModel);

    glm::mat4 tableModel = glm::translate(I4, config::TABLE_POSITION);
    hotelRoom->children["table"][0] =
        std::make_unique<ModelInstance>(tableAsset.get(), tableModel, hotelRoom.get());

    // Temporarily remove the door between the hotel room and swamp room until door unlocking is
    // implemented
    std::array<float, 3> degrees = {90.0f, 180.0f, 270.0f}; // Add 0.0f later

    for (int i = 0; i < degrees.size(); ++i) {
        glm::mat4 doorModel =
            glm::rotate(I4, glm::radians(degrees[i]), glm::vec3(0.0f, 1.0f, 0.0f));
        doorModel = glm::translate(doorModel, glm::vec3(10.0f, 0.0f, 0.0f));
        hotelRoom->children["door"][i] =
            std::make_unique<ModelInstance>(doorAsset.get(), doorModel, hotelRoom.get());
    }

    // Swamp room
    glm::mat4 swampRoomModel = glm::translate(I4, config::SWAMP_ROOM_POSITION);
    auto swampRoom = std::make_unique<ModelInstance>(swampRoomAsset.get(), swampRoomModel);

    for (int i = 0; i < config::SWAMP_NUM_LILYPADS; i++) {
        glm::mat4 lilypadModel =
            glm::translate(I4, glm::vec3(22.0f + (i / 2) * 8.0f, 0.0f, ((i % 2) * -2 + 1) * 3.0f));

        float angleDegrees = fmod(i * 137.0f, 360.0f);
        lilypadModel =
            glm::rotate(lilypadModel, glm::radians(angleDegrees), glm::vec3(0.0f, 1.0f, 0.0f));

        swampRoom->children["lilypad"][i] =
            std::make_unique<ModelInstance>(lilypadAsset.get(), lilypadModel, swampRoom.get());
    }

    modelInstances["hotelRoom"] = std::move(hotelRoom);
    modelInstances["swampRoom"] = std::move(swampRoom);
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
    for (auto& [name, shader] : shaders) {
        shader->use();
        shader->setMat4("view", camera.getViewMatrix());
        shader->setMat4("projection", camera.getProjectionMatrix());
        shader->setVec3("viewPos", camera.getPosition());
    }

    // Draw all model instances in the scene
    for (const auto& [name, instance] : modelInstances) {
        if (name == "hotelRoom") {
            shaders["model"]->use();

            // This is for testing, will change this later
            std::vector<PointLight> testLights = {
                {glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f)},
            };

            // This is for testing, will change this later
            shaders["model"]->setInt("numLights", testLights.size());
            for (int i = 0; i < testLights.size(); ++i) {
                shaders["model"]->setVec3("pointLights[" + std::to_string(i) + "].position",
                                          testLights[i].position);
                shaders["model"]->setVec3("pointLights[" + std::to_string(i) + "].color",
                                          testLights[i].color);
            }

            instance->drawRecursive(*shaders["model"], boundingBoxMode);
        } else if (name == "swampRoom") {
            shaders["swamp"]->use();

            // This is for testing, will change this later
            std::vector<PointLight> testLights = {
                {glm::vec3(30.0f, 10.0f, 0.0f), glm::vec3(1.0f)},
                {glm::vec3(60.0f, 7.0f, 0.0f), glm::vec3(1.0f)},
            };

            // This is for testing, will change this later
            shaders["swamp"]->setInt("numLights", testLights.size());
            for (int i = 0; i < testLights.size(); ++i) {
                shaders["swamp"]->setVec3("pointLights[" + std::to_string(i) + "].position",
                                          testLights[i].position);
                shaders["swamp"]->setVec3("pointLights[" + std::to_string(i) + "].color",
                                          testLights[i].color);
            }

            instance->drawRecursive(*shaders["swamp"], boundingBoxMode);
        }
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
