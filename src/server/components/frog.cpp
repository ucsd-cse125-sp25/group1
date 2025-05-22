#include "components/frog.hpp"

Frog::Frog(int id, glm::vec3 position, glm::vec3 direction, float width, float height)
    : Interactable(id, position, direction, width, height) {}

void Frog::handleInteract(const Player& player) {
    // Define behavior here
}