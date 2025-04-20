#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <optional>
#include <unordered_map>
#include "camera.hpp"
#include "config.hpp"
#include "cube.hpp"
#include "shader.hpp"

struct Player {
    int id;
    glm::vec3 position;

    std::unique_ptr<Cube> character;

    Player(int id, const glm::vec3& position)
        : id(id), position(position), character(std::make_unique<Cube>()) {}
    
    void draw(Shader& shader) {
        glm::mat4 playerModel = glm::translate(glm::mat4(1.0f), position);
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
    void updatePlayerPosition(int id, const glm::vec3& position);
    void render();

private:
    std::optional<Camera> camera;
    std::unique_ptr<Shader> shader;
    
    std::unique_ptr<Cube> floor;

    std::unordered_map<int, Player> players;
};
