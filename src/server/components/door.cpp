#include <stdexcept>
#include "server/components/door.hpp"

Door::Door(int doorID, int room1, int room2, int keyID, glm::vec3 position, glm::vec3 direction)
    : Interactable(),
    doorID(doorID),
    keyID(keyID),
    locked(keyID != -1),
    open(false),
    body(
        vec3(0.0f),
        vec3(0.0f),
        0.0f, // mass of 0 - kinematics doesn't matter because it's static (imovable)
        new Transform { position, direction },
        new BoxCollider{
            AABB,
            vec3(-config::PLAYER_WIDTH / 2, -config::PLAYER_HEIGHT / 2, -config::PLAYER_WIDTH / 2),
            vec3(config::PLAYER_WIDTH / 2, config::PLAYER_HEIGHT / 2, config::PLAYER_WIDTH / 2)
        },
        true
    )
{
    rooms[0] = room1;
    rooms[1] = room2;
}

Door::Door(int doorID, int room1, int room2, glm::vec3 position, glm::vec3 direction)
    : Door(doorID, room1, room2, -1, position, direction){}

int Door::getDestinationRoomID(int currRoomID) const {
    if (currRoomID == rooms[0]){
        return rooms[1];
    }
    if (currRoomID == rooms[1]){
        return rooms[0];
    }
    throw std::invalid_argument("Door::getDestinationRoomID: bad currRoomID");
}

void Door::handleInteract(const Player &player) {
    if (!locked){
        openDoor();
        return;
    }
    // if the player has the key to unlock the door, unlock and open it.
    if (player.getKeyIDs().count(keyID) > 0){
        unlockDoor();
        openDoor();
    }
}

void Door::openDoor(){
    open = true;
    // TODO: play door opening animation and move rigid body
}

void Door::unlockDoor(){
    locked = false;
    // TODO: play door unlocking animation
}