#include "firefly.hpp"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

Firefly::Firefly(const glm::vec3& position, const glm::vec3& direction, float speed,
                 const glm::vec3& center, const glm::vec3& half)
    : position(position), direction(glm::normalize(direction)), speed(speed),
      minBound(center - half), maxBound(center + half), size(glm::linearRand(0, 1) ? 4.0f : 5.0f) {}

void Firefly::update(float deltaTime) {
    position += direction * speed * deltaTime;

    for (int i = 0; i < 3; ++i) {
        if (position[i] < minBound[i] || position[i] > maxBound[i]) {
            direction[i] *= -1.0f;
            position[i] = glm::clamp(position[i], minBound[i], maxBound[i]);
        }
    }
}
