#include "components/interactable.hpp"

Interactable::Interactable(int id, const glm::vec3& position, const glm::vec3& direction,
                           float width, float height)
    : Object(id, position, direction, width, height) {}

void Interactable::interact(const Player& player) {
    handleInteract(player);
}
