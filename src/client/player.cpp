#include "player.hpp"
#include <glm/gtc/matrix_transform.hpp>

Player::Player(int id, const glm::vec3& position, const glm::vec3& direction)
    : id(id),
      position(position),
      direction(direction),
      // TODO: init currRoomID to the id of the lobby
      character(std::make_unique<Cube>()) {}


void Player::draw(Shader& shader) {
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