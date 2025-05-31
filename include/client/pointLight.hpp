#include <glm/glm.hpp>
#include <string>
#include <vector>

/**
 * @brief Represents a point light with a position and color.
 *
 * The position is calculated in world space using the local position
 * and the room's transformation matrix.
 */
struct PointLight {
    glm::vec3 worldPosition;
    glm::vec3 color;

    /**
     * @brief Constructs a PointLight in world space.
     * @param roomTransform Transformation matrix of the room.
     * @param localPosition Light position relative to the room.
     * @param color RGB color of the light.
     */
    PointLight(const glm::mat4& roomTransform, const glm::vec3& localPosition,
               const glm::vec3& color)
        : color(color) {
        worldPosition = glm::vec3(roomTransform * glm::vec4(localPosition, 1.0f));
    }
};
