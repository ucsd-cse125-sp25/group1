#include "client/components/room.hpp"

Room::Room(int id, const std::string& name)
    : roomID(id), roomName(name)
{
    // Todo: any additional initialization (i.e. doors) if needed
}

Room::~Room(){
    // Nothing todo yet; free any dynamically allocated in the future if added.
}

int Room::getID() const{
    return roomID;
}

std::string Room::getName() const{
    return roomName;
}

void Room::addInteractable(std::unique_ptr<Interactable> object) {
    interactables.push_back(std::move(object));
}

// return a vector of raw pointers for read-only access
std::vector<Interactable*> Room::getInteractables() const {
    std::vector<Interactable*> out;
    out.reserve(interactables.size());
    for (auto& uptr : interactables)
        out.push_back(uptr.get());
    return out;
}

void Room::removeInteractable(Interactable* object) {
    auto it = std::remove_if(
      interactables.begin(),
      interactables.end(),
      [object](auto const& up) { return up.get() == object; }
    );
    interactables.erase(it, interactables.end());
  }