#include "components/interactable.hpp"

Interactable::Interactable(int id) : Object(id) {}

Interactable::Interactable() : Interactable(-1) {}
void Interactable::interact(Player& player) {
    handleInteract(player);
}

void Interactable::addRoom(Room* room) {
    roomPtrs.push_back(room);
}
