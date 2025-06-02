#include "components/room.hpp"
#include <algorithm>

Room::Room(int id, const std::string& name) : roomID(id), roomName(name) {
    // Todo: any additional initialization (i.e. doors) if needed
}

Room::~Room() {
    // Nothing todo yet; free any dynamically allocated in the future if added.
}

int Room::getID() const {
    return roomID;
}

std::string Room::getName() const {
    return roomName;
}

void Room::addInteractable(Interactable* object) {
    this->interactables.push_back(object);
}

// return a vector of raw pointers for read-only access
std::vector<Interactable*> Room::getInteractables() const {
    return this->interactables;
}

void Room::removeInteractable(Interactable* object) {
    auto it = std::remove_if(this->interactables.begin(), this->interactables.end(),
                             [object](auto const& up) { return up == object; });
    this->interactables.erase(it, this->interactables.end());
}
