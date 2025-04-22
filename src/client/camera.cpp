#include "camera.hpp"
#include "config.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera()
    : position(0.0f),
      direction(0.0f, 0.0f, 1.0f),
      up(0.0f, 1.0f, 0.0f),
      fovy(config::FOVY),
      aspect(static_cast<float>(config::WORLD_WIDTH) / config::WORLD_HEIGHT),
      near(config::NEAR_CLIP),
      far(config::FAR_CLIP) {}

void Camera::setPosition(const glm::vec3& position) {
    this->position = position;
}

void Camera::setDirection(const glm::vec3& direction) {
    this->direction = glm::normalize(direction);
}

void Camera::setUp(const glm::vec3& up) {
    this->up = glm::normalize(up);
}

void Camera::move(const glm::vec3& delta) {
    position += delta;
}

void Camera::moveForward(float distance) {
    move(direction * distance);
}

void Camera::moveRight(float distance) {
    glm::vec3 right = glm::normalize(glm::cross(direction, up));
    move(right * distance);
}

void Camera::moveUp(float distance) {
    move(up * distance);
}

void Camera::rotateYaw(float degrees) {
    direction = glm::rotateY(direction, glm::radians(degrees));
}

void Camera::rotatePitch(float degrees) {
    glm::vec3 right = glm::normalize(glm::cross(direction, up));
    direction = glm::normalize(glm::rotate(direction, glm::radians(degrees), right));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + direction, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fovy), aspect, near, far);
}
