#pragma once

#include <glm/glm.hpp>

/**
 * @brief Represents a single firefly that moves within a 3D bounding box.
 */
class Firefly {
  public:
    glm::vec3 position;
    glm::vec3 direction;

    float speed;
    float size;

    glm::vec3 minBound;
    glm::vec3 maxBound;

    /**
     * @brief Constructs a firefly with initial state and movement bounds.
     *
     * @param position Initial position.
     * @param direction Initial direction.
     * @param speed Speed.
     * @param minBound Minimum corner of the bounding area.
     * @param maxBound Maximum corner of the bounding area.
     */
    Firefly(const glm::vec3& position, const glm::vec3& direction, float speed,
            const glm::vec3& minBound, const glm::vec3& maxBound);

    /**
     * @brief Updates the firefly's position based on direction and speed.
     *
     * Reverses direction and clamps position if it hits the bounding limits.
     *
     * @param deltaTime Time passed since the last update.
     */
    void update(float deltaTime);
};
