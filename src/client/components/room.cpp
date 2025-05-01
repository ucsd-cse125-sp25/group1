#include "components/room.hpp"

Room::Room(int id) : roomID(id) {
    // Constructor implementation
}

Room::~Room() {
    // Destructor implementation
}

int Room::getID() const {
    return roomID;
}