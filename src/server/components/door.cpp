#include "components/door.hpp"

Door::Door(int doorID, int room1, int room2, int keyID, glm::vec3 position, glm::vec3 direction)
    : Interactable(doorID, position, direction, config::PLAYER_WIDTH, config::PLAYER_HEIGHT),
    doorID(doorID),
    keyID(keyID),
    locked(keyID != -1),
    open(false),
    body(
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        0.0f, // mass of 0 - kinematics doesn't matter because it's static (imovable)
        new Transform { position, direction },
        new BoxCollider{
            AABB,
            // TODO: why is this the dimensions of a door?
            glm::vec3(-config::PLAYER_WIDTH / 2, -config::PLAYER_HEIGHT / 2, -config::PLAYER_WIDTH / 2),
            glm::vec3(config::PLAYER_WIDTH / 2, config::PLAYER_HEIGHT / 2, config::PLAYER_WIDTH / 2)
        },
        nullptr,
        true
    )
{
    rooms[0] = room1;
    rooms[1] = room2;
}

Door::Door(int doorID, int room1, int room2, glm::vec3 position, glm::vec3 direction)
    : Door(doorID, room1, room2, -1, position, direction){}

void Door::handleInteract(const Player &player) {
    if (!locked){
        openDoor();
    }
    // if the player has the key to unlock the door, unlock and open it.
    else if (player.getKeyIDs().count(keyID) > 0){
        unlockDoor();
        openDoor();
    }
    // TODO: send message to client of whether the open worked.
}

void Door::openDoor(){
    open = true;
    // TODO: move rigid body
}

void Door::unlockDoor(){
    locked = false;
}