#include "player.hpp"
#include <glm/gtc/matrix_transform.hpp>

Player::Player(int id, const glm::vec3& position, const glm::vec3& direction)
    : id(id), position(position), direction(direction) {}
// TODO: init currRoomID to the id of the lobby

void Player::init() {
    character = std::make_unique<AnimatedModel>("../src/client/characters/player_cat.fbx");
    animations["idle"] = std::make_unique<Animation>(character->getScene(), character.get());
    animator = std::make_unique<Animator>(animations["idle"].get());
}

void Player::draw(Shader& shader) {
    const auto& boneMatrices = animator->getBoneMatrices();

    for (int i = 0; i < boneMatrices.size(); ++i) {
        shader.setMat4("boneMatrices[" + std::to_string(i) + "]", boneMatrices[i]);
    }

    glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 rotationAxis = glm::cross(forward, direction);

    if (glm::length(rotationAxis) < 0.0001f) {
        rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    float dot = glm::dot(forward, direction);
    float angle = acos(glm::clamp(dot, -1.0f, 1.0f));

    glm::mat4 playerModel = glm::translate(glm::mat4(1.0f), position);
    playerModel = glm::rotate(playerModel, angle, glm::normalize(rotationAxis));

    shader.setMat4("model", playerModel);

    character->draw(shader);
}
