#include "components/door.hpp"
#include "server.hpp"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

Door::Door(int doorID, int room1, int room2, int keyID, Server& serverRef)
    : Interactable(doorID), keyID(keyID), locked(keyID != -1), open(false), server(serverRef) {
    rooms[0] = room1;
    rooms[1] = room2;
}

Door::Door(int doorID, int room1, int room2, Server& serverRef)
    : Door(doorID, room1, room2, -1, serverRef) {
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

void Door::handleInteract(Player& player) {
    if (!locked) {
        openDoor(player.getID());
    }
    // if the player has the key to unlock the door, unlock and open it.
    else if (player.getKeyIDs().count(keyID) > 0) {
        unlockDoor();
        openDoor(player.getID());
    }
    // TODO: send message to client of whether the open worked.
}

void Door::openDoor(int playerId) {
    open = true;
    for (int i = 0; i < roomPtrs.size(); i++) {
        Room* room = roomPtrs[i];
        room->removeInteractable(static_cast<Interactable*>(this));
    }
    delete body;
    this->setBody(nullptr);

    json sfx;
    sfx["type"] = "sfx";
    sfx["sfx_id"] = config::UNLOCKDOOR;
    sfx["client_id"] = playerId;
    sfx["action"] = "door_open";
    sfx["volume"] = config::UNLOCKDOOR_VOL;

    std::string sfxPacket = sfx.dump() + "\n";
    server.broadcastMessage(sfxPacket);

    std::cout << "open door called on " << this->getID() << std::endl;
}

void Door::unlockDoor() {
    locked = false;
}
