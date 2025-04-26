#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <unordered_map>
#include "camera.hpp"
#include "config.hpp"
#include "cube.hpp"
#include "model.hpp"
#include "shader.hpp"

struct Player {
    int id;
    glm::vec3 position;
    glm::vec3 direction;

    std::unique_ptr<Cube> character;

    Player(int id, const glm::vec3& position, const glm::vec3& direction)
        : id(id),
          position(position),
          direction(direction),
          character(std::make_unique<Cube>()) {}

    void draw(Shader& shader) {
        glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 rotationAxis = glm::cross(forward, direction);

        if (glm::length(rotationAxis) < 0.0001f) {
            rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
        }

        float dot = glm::dot(forward, direction);
        float angle = acos(glm::clamp(dot, -1.0f, 1.0f));

        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::normalize(rotationAxis));
        glm::mat4 playerModel = glm::translate(glm::mat4(1.0f), position);
        playerModel *= rotation;

        shader.setMat4("model", playerModel);
        shader.setVec3("color", config::PLAYER_COLORS[id]);
        character->draw();
    }
};

class Scene {
public:
    Scene();
    ~Scene();

    void init(int clientId);

    void updatePlayerState(int id, const glm::vec3& position, const glm::vec3& direction);
    void removePlayer(int id);

    void render(const Camera& camera);

private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> modelShader;

    std::unique_ptr<Model> room;
    std::unique_ptr<Model> table;

    std::unordered_map<int, Player> players;
};
