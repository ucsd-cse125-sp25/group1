#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    Camera(const glm::vec3& position);

    void setPosition(const glm::vec3& position);
    void setDirection(const glm::vec3& direction);
    void setUp(const glm::vec3& up);

    void move(const glm::vec3& delta);
    void moveForward(float distance);
    void moveRight(float distance);
    void moveUp(float distance);
    
    void rotateYaw(float degrees);
    void rotatePitch(float degrees);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;

    float fovy;
    float aspect;
    float near;
    float far;
};
