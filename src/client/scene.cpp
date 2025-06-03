#include "scene.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <array>
#include <cmath>
#include <glad/glad.h>
#include <iostream>
#include <vector>

static const glm::mat4 I4{1.0f};

Scene::Scene(int playerID) : playerID(playerID) {}
Scene::~Scene() {}

void Scene::init() {
    shaders["character"] = std::make_unique<Shader>("../src/client/shaders/character.vert",
                                                    "../src/client/shaders/character.frag");

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
    frogAsset = std::make_unique<Model>("../src/client/models/froggie.obj");

    circusRoomAsset = std::make_unique<Model>("../src/client/models/tent.obj");

    keyAsset = std::make_unique<Model>("../src/client/models/key.obj");

    canvas = std::make_unique<Canvas>();

    initRooms();
    initLights();
    initShadowMaps();

    renderStaticShadowPass();
    renderInteractableShadowPass();

    spawnFireflies(config::SWAMP_NUM_FIREFLIES);
}

void Scene::initRooms() {
    // Hotel room
    glm::mat4 hotelRoomModel = glm::translate(I4, config::HOTEL_ROOM_POSITION);
    auto hotelRoom =
        std::make_unique<ModelInstance>(hotelRoomAsset.get(), hotelRoomModel, nullptr, true);

    glm::mat4 tableModel = glm::translate(I4, config::TABLE_POSITION);
    hotelRoom->children["table"][0] =
        std::make_unique<ModelInstance>(tableAsset.get(), tableModel, hotelRoom.get(), true);

    std::array<float, 1> degrees = {90.0f}; // Add 0.0f, 180.0f 270.0f later

    for (int i = 0; i < degrees.size(); ++i) {
        glm::mat4 doorModel =
            glm::rotate(I4, glm::radians(degrees[i]), glm::vec3(0.0f, 1.0f, 0.0f));
        doorModel = glm::translate(doorModel, glm::vec3(10.0f, 0.0f, 0.0f));
        hotelRoom->children["door"][i] =
            std::make_unique<ModelInstance>(doorAsset.get(), doorModel, hotelRoom.get(), false);
    }

    // Parkour rooms
    glm::mat4 parkourRoom1Model = glm::translate(I4, config::PARKOUR_ROOM_1_POSITION);
    auto parkourRoom1 = std::make_unique<ModelInstance>(hotelRoomAsset.get(), parkourRoom1Model);
    glm::mat4 parkour1Key = glm::translate(I4, config::PARKOUR_1_KEY_POSITION);
    parkourRoom1->children["key"][0] =
        std::make_unique<ModelInstance>(keyAsset.get(), parkour1Key, parkourRoom1.get(), false);

    glm::mat4 parkour1Table1 = glm::translate(I4, config::PARKOUR_1_TABLE_1_POSITION);
    parkourRoom1->children["table"][0] =
        std::make_unique<ModelInstance>(tableAsset.get(), parkour1Table1, parkourRoom1.get());

    glm::mat4 parkour1Table2 = glm::translate(I4, config::PARKOUR_1_TABLE_2_POSITION);
    parkourRoom1->children["table"][1] =
        std::make_unique<ModelInstance>(tableAsset.get(), parkour1Table2, parkourRoom1.get());

    glm::mat4 parkour1Table3 = glm::translate(I4, config::PARKOUR_1_TABLE_3_POSITION);
    parkourRoom1->children["table"][2] =
        std::make_unique<ModelInstance>(tableAsset.get(), parkour1Table3, parkourRoom1.get());

    // Swamp room
    glm::mat4 swampRoomModel = glm::translate(I4, config::SWAMP_ROOM_POSITION);
    auto swampRoom =
        std::make_unique<ModelInstance>(swampRoomAsset.get(), swampRoomModel, nullptr, true);

    for (int i = 0; i < config::SWAMP_NUM_LILYPADS; i++) {
        glm::mat4 lilypadModel =
            glm::translate(I4, glm::vec3(22.0f + (i / 2) * 8.0f, 0.0f, ((i % 2) * -2 + 1) * 3.0f));

        float angleDegrees = fmod(i * 137.0f, 360.0f);
        lilypadModel =
            glm::rotate(lilypadModel, glm::radians(angleDegrees), glm::vec3(0.0f, 1.0f, 0.0f));

        swampRoom->children["lilypad"][i] = std::make_unique<ModelInstance>(
            lilypadAsset.get(), lilypadModel, swampRoom.get(), false);
    }

    glm::mat4 frogModel = glm::translate(I4, config::FROG_POSITION);
    frogModel = glm::rotate(frogModel, glm::radians(-120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    swampRoom->children["frog"][0] =
        std::make_unique<ModelInstance>(frogAsset.get(), frogModel, swampRoom.get(), true);

    // Circus room
    glm::mat4 circusRoomModel = glm::translate(I4, config::CIRCUS_ROOM_POSITION);
    auto circusRoom =
        std::make_unique<ModelInstance>(circusRoomAsset.get(), circusRoomModel, nullptr, true);

    // Swamp key room
    glm::mat4 swampKeyRoomModel = glm::translate(I4, config::SWAMPKEY_ROOM_POSITION);
    auto swampKeyRoom =
        std::make_unique<ModelInstance>(hotelRoomAsset.get(), swampKeyRoomModel, nullptr, true);

    glm::mat4 swampKey = glm::translate(I4, config::SWAMP_KEY_POSITION);
    swampKey = glm::rotate(swampKey, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    swampKeyRoom->children["key"][0] =
        std::make_unique<ModelInstance>(keyAsset.get(), swampKey, swampKeyRoom.get(), false);

    modelInstances["hotelRoom"] = std::move(hotelRoom);
    modelInstances["swampRoom"] = std::move(swampRoom);
    modelInstances["parkourRoom1"] = std::move(parkourRoom1);
    modelInstances["swampKeyRoom"] = std::move(swampKeyRoom);
    modelInstances["circusRoom"] = std::move(circusRoom);
}

void Scene::initLights() {
    pointLights["hotelRoom"] = {PointLight(glm::translate(I4, config::HOTEL_ROOM_POSITION),
                                           glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["swampRoom"] = {PointLight(glm::translate(I4, config::SWAMP_ROOM_POSITION),
                                           glm::vec3(30.0f, 7.0f, 0.0f), glm::vec3(0.7f)),
                                PointLight(glm::translate(I4, config::SWAMP_ROOM_POSITION),
                                           glm::vec3(70.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["circusRoom"] = {PointLight(glm::translate(I4, config::CIRCUS_ROOM_POSITION),
                                            glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["swampKeyRoom"] = {PointLight(glm::translate(I4, config::SWAMPKEY_ROOM_POSITION),
                                              glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["parkourRoom1"] = {PointLight(glm::translate(I4, config::PARKOUR_ROOM_1_POSITION),
                                              glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
}

void Scene::initShadowMaps() {
    for (const auto& [name, lights] : pointLights) {
        for (const PointLight& light : lights) {
            auto staticShadowMap =
                std::make_unique<ShadowMap>(light.worldPosition, config::SHADOW_MAP_RES_STATIC);
            staticShadowMaps[name].emplace_back(std::move(staticShadowMap));

            auto interactableShadowMap = std::make_unique<ShadowMap>(
                light.worldPosition, config::SHADOW_MAP_RES_INTERACTABLE);
            interactableShadowMaps[name].emplace_back(std::move(interactableShadowMap));
            interactableShadowActive[name].emplace_back(false);
        }
    }
}

void Scene::updatePlayerState(int id, const glm::vec3& position, const glm::vec3& direction) {
    if (!players.contains(id)) {
        auto [it, inserted] = players.emplace(id, Player(id, position, direction));
        if (inserted) {
            it->second.init();
        }
    } else {
        players.at(id).setPosition(position);
        players.at(id).setDirection(direction);
    }
}

void Scene::updateWindow() {
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    canvas->updateWindow(width, height);
}

void Scene::removePlayer(int id) {
    players.erase(id);
}

void Scene::removeInstanceFromRoom(const std::string& roomName, const std::string& type, int id) {
    modelInstances[roomName]->deleteChild(type, id);
}

void Scene::renderStaticShadowPass() {
    for (auto& [name, shadowMaps] : staticShadowMaps) {
        for (const auto& shadowMap : shadowMaps) {
            shadowMap->begin();

            Shader& shader = shadowMap->getShader();
            shader.setBool("isSkinned", false);
            modelInstances[name]->drawRecursive(shader, false, true);

            shadowMap->end();
        }
    }
}

void Scene::renderInteractableShadowPass() {
    renderLilypadShadowPass();

    // Will refactor this if more interactable things (other than a key) are added
    std::vector<std::string> keyRooms = {"swampKeyRoom", "parkourRoom1"};
    for (const std::string& roomName : keyRooms) {
        auto& shadowMaps = interactableShadowMaps[roomName];
        shadowMaps[0]->begin();

        Shader& shader = shadowMaps[0]->getShader();
        shader.setBool("isSkinned", false);
        modelInstances[roomName]->drawInteractable(shader, "key");

        shadowMaps[0]->end();
        interactableShadowActive[roomName][0] = true;
    }
}

void Scene::spawnFireflies(int count) {
    glm::vec3 center = config::SWAMP_ROOM_POSITION + glm::vec3(50.0f, 5.0f, 0.0f);
    glm::vec3 half = glm::vec3(35.0f, 5.0f, 30.0f);

    for (int i = 0; i < count; ++i) {
        glm::vec3 position = center + glm::linearRand(-half, half);
        glm::vec3 direction = glm::sphericalRand(1.0f);
        float speed = glm::linearRand(0.5f, 1.5f);

        fireflies.emplace_back(position, direction, speed, center, half);
    }
}

void Scene::renderLilypadShadowPass(int id) {
    auto& shadowMaps = interactableShadowMaps["swampRoom"];

    auto renderForIndex = [&](int index) {
        shadowMaps[index]->begin();
        Shader& shader = shadowMaps[index]->getShader();
        shader.setBool("isSkinned", false);

        int start = (index == 0) ? 0 : 8;
        int end = (index == 0) ? 7 : 15;
        modelInstances["swampRoom"]->drawInteractable(shader, "lilypad", start, end);

        shadowMaps[index]->end();
    };

    if (id == -1) {
        for (int i = 0; i < 2; ++i) {
            renderForIndex(i);
            interactableShadowActive["swampRoom"][i] = true;
        }
    } else {
        renderForIndex((id < 8) ? 0 : 1);
    }
}

void Scene::render(const Camera& camera, bool boundingBoxMode) {
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    shaders["character"]->use();

    for (auto& [id, player] : players) {
        if (id == playerID)
            continue;

        player.updateTime(deltaTime);
        player.draw(*shaders["character"]);
    }

    for (auto& [name, shader] : shaders) {
        shader->use();

        shader->setMat4("view", camera.getViewMatrix());
        shader->setMat4("projection", camera.getProjectionMatrix());
        shader->setVec3("viewPos", camera.getPosition());

        if (name == "character") {
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            shader->setInt("shadowDepthCubemap" + std::to_string(i),
                           config::SHADOW_TEXTURE_UNIT + i);
        }

        shader->setFloat("shadowFarClip", config::SHADOW_FAR_CLIP);
    }

    // Draw all model instances in the scene
    for (const auto& [name, instance] : modelInstances) {
        Shader* shader = nullptr;
        const auto& lights = pointLights[name];

        for (int i = 0; i < 2; ++i) {
            glActiveTexture(GL_TEXTURE0 + config::SHADOW_TEXTURE_UNIT + i);
            GLuint tex = (i < lights.size()) ? staticShadowMaps[name][i]->getDepthCubemap()
                                             : getDummyCubemap();
            glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

            glActiveTexture(GL_TEXTURE0 + config::SHADOW_TEXTURE_UNIT + i + 2);
            tex = i < (lights.size()) ? interactableShadowMaps[name][i]->getDepthCubemap()
                                      : getDummyCubemap();
            glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
        }

        if (name == "hotelRoom" || name == "swampKeyRoom" || name == "parkourRoom1") {
            shader = shaders["model"].get();
            shader->use();
            shader->setBool("useFade", false);
        } else if (name == "swampRoom") {
            shader = shaders["swamp"].get();
            shader->use();
            shader->setBool("useFog", true);
            shader->setVec3("fogColor", glm::vec3(0.05f, 0.07f, 0.1f));
            shader->setFloat("fogStart", 10.0f);
            shader->setFloat("fogEnd", 60.0f);
        } else if (name == "circusRoom") {
            shader = shaders["model"].get();
            shader->use();
            shader->setBool("useFade", true);
        }

        shader->setInt("numLights", lights.size());

        for (int i = 0; i < lights.size(); ++i) {
            shader->setVec3("pointLights[" + std::to_string(i) + "].position",
                            lights[i].worldPosition);
            shader->setVec3("pointLights[" + std::to_string(i) + "].color", lights[i].color);
            shader->setBool("interactableShadowActive[" + std::to_string(i) + "]",
                            interactableShadowActive[name][i]);
        }

        instance->drawRecursive(*shader, boundingBoxMode);
    }

    for (Firefly& firefly : fireflies) {
        firefly.update(deltaTime);
    }

    fireflyRenderer.draw(fireflies, camera.getViewMatrix(), camera.getProjectionMatrix());

    // UI
    updateWindow();
    canvas->draw(*uiShader);
}
