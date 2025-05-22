#include "client/components/door.hpp"
#include <stdexcept>

Door::Door(int doorID, int room1, int room2, bool isLocked)
    : Interactable(), doorID(doorID), locked(isLocked), open(false) {
    rooms[0] = room1;
    rooms[1] = room2;
}

int Door::getDestinationRoomID(int currRoomID) const {
    if (currRoomID == rooms[0]) {
        return rooms[1];
    }
    if (currRoomID == rooms[1]) {
        return rooms[0];
    }
    throw std::invalid_argument("Door::getDestinationRoomID: bad currRoomID");
}

bool Door::isLocked() const {
    return locked;
}

bool Door::isOpen() const {
    return open;
}

void Door::sendInteractRequest(int playerID) {
    // TODO: send message to server that the given player (ID) is attempting to open the door.
}

void Door::processInteractResult(bool state) {
    tryOpen(state);
}

void Door::unlockDoor() {
    locked = false;
    // TODO: play door unlocking animation
}

void Door::openDoor() {
    open = true;
    // TODO: play door opening animation and move position of door
}

void Door::tryOpen(bool success) {
    // attempt to unlock door (if it has a lock)
    if (locked) {
        if (success) {
            unlockDoor();
        } else {
            // TODO: play animation of door shuddering (not opening because it's locked)
        }
    }
    // attempt to open door
    if (success) {
        openDoor();
    }
}
