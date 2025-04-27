#pragma once

#include <glm/glm.hpp>

/**
 * @brief Represents a simple 3D camera for viewing a scene.
 * 
 * Provides functionality to control the camera's position, orientation, and projection.
 */
class Camera {
public:
    /**
     * @brief Constructs a Camera instance with default parameters.
     * 
     * Initializes position, direction, up, fovy, aspect, nearClip, and farClip.
     */
    Camera();

    /**
     * @brief Sets the camera's position in world space.
     * 
     * @param position New position vector.
     */
    void setPosition(const glm::vec3& position);

    /**
     * @brief Sets the camera's viewing direction.
     * 
     * @param direction New direction vector.
     */
    void setDirection(const glm::vec3& direction);

    /**
     * @brief Sets the camera's up vector.
     * 
     * @param up New up vector.
     */
    void setUp(const glm::vec3& up);

    /**
     * @brief Sets the camera's aspect ratio.
     * 
     * @param aspect New aspect ratio (width / height).
     */
    void setAspect(float aspect);

    /**
     * @brief Moves the camera by a given delta vector.
     * 
     * @param delta Offset to add to the current position.
     */
    void move(const glm::vec3& delta);

    /**
     * @brief Moves the camera forward relative to its direction.
     * 
     * @param distance Distance to move forward.
     */
    void moveForward(float distance);

    /**
     * @brief Moves the camera to the right relative to its direction.
     * 
     * @param distance Distance to move right.
     */
    void moveRight(float distance);

    /**
     * @brief Moves the camera upward relative to its up vector.
     * 
     * @param distance Distance to move upward.
     */
    void moveUp(float distance);
    
    /**
     * @brief Rotates the camera around the up axis (yaw).
     * 
     * @param degrees Angle to rotate in degrees.
     */
    void rotateYaw(float degrees);

    /**
     * @brief Rotates the camera around the right axis (pitch).
     * 
     * @param degrees Angle to rotate in degrees.
     */
    void rotatePitch(float degrees);

    /**
     * @brief Retrieves the view matrix for rendering.
     * 
     * @return View matrix based on position, direction, and up vector.
     */
    glm::mat4 getViewMatrix() const;

    /**
     * @brief Retrieves the projection matrix for rendering.
     * 
     * @return Projection matrix based on FOVY, aspect ratio, and clipping planes.
     */
    glm::mat4 getProjectionMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;

    float fovy;
    float aspect;
    float nearClip;
    float farClip;
};
