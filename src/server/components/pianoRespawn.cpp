#include "components/pianoRespawn.hpp"
#include <iostream>
#include "json.hpp"
#include "player.hpp"
#include "server.hpp"

using json = nlohmann::json;

PianoRespawn::PianoRespawn(int id) : Object(id) {}

void PianoRespawn::customCollision(ICustomPhysics* otherObject) {
    auto* playerPtr = dynamic_cast<Player*>(otherObject);
    // make sure it's a player that hit the water plane
    if (!playerPtr) {
        return;
    }
    // respawn player at the spawn point
    RigidBody& playerBody = playerPtr->getBody();
    // Make sure the player has no residual movement on respawn
    playerBody.setForce(glm::vec3{0.0f, 0.0f, 0.0f});
    playerBody.setVelocity(glm::vec3{0.0f, 0.0f, 0.0f});
    // TODO: add offset for the individual player, so 2 players don't spawn into the same spot.
    playerBody.setPosition(config::PIANO_RESPAWN + config::PIANO_ROOM_POSITION +
                           config::PIANO_OFFSET[playerPtr->getID()]);
    playerPtr->setJumpSfxCooldown(false);
}
