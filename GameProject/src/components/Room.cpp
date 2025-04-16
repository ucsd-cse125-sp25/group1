#include "components/Room.h"

// Todo: add function definitions
Room::Room(int id, const std::string& name)
    : roomID(id), roomName(name)
{
    // Todo: any additional initialization (doors?) if needed
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

void Room::addInteractable(Interactable* object){
    interactables.push_back(object);
}

// Todo: add getInteractables, removeInteractable functions