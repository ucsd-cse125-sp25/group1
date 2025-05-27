#include "components/interactable.hpp"

Interactable::Interactable(int id) : Object(id) {}

void Interactable::interact(const Player& player) {
    handleInteract(player);
}
