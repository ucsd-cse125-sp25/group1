#include "components/door.hpp"

Door::Door(int doorID, int room1, int room2, int keyID)
    : Interactable(doorID),
      doorID(doorID), keyID(keyID), locked(keyID != -1), open(false) {
    rooms[0] = room1;
    rooms[1] = room2;
}

Door::Door(int doorID, int room1, int room2)
    : Interactable(doorID),
      doorID(doorID), open(false) {
    rooms[0] = room1;
    rooms[1] = room2;
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
    // TODO: move rigid body
}

void Door::unlockDoor() {
    locked = false;
}
