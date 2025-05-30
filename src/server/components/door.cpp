#include "components/door.hpp"

Door::Door(int doorID, int room1, int room2, int keyID)
    : Interactable(doorID), keyID(keyID), locked(keyID != -1), open(false) {
    rooms[0] = room1;
    rooms[1] = room2;
}

Door::Door(int doorID, int room1, int room2) : Door(doorID, room1, room2, -1) {
    rooms[0] = room1;
    rooms[1] = room2;
}

void Door::setRoomZones(RigidBody* room1, RigidBody* room2) {
    roomZones[0] = room1;
    roomZones[1] = room2;
}

int Door::getRoomID(int index) const {
    return rooms[index];
}

void Door::handleInteract(const Player& player) {
    if (!locked) {
        openDoor();
    }
    // if the player has the key to unlock the door, unlock and open it.
    else if (player.getKeyIDs().count(keyID) > 0) {
        unlockDoor();
        openDoor();
    }
    // TODO: send message to client of whether the open worked.
}

void Door::openDoor() {
    open = true;
    delete this->getBody();
    this->setBody(nullptr);
}

void Door::unlockDoor() {
    locked = false;
}
