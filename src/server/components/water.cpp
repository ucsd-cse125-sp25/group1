#include "components/water.hpp"
#include <iostream>
#include "player.hpp"

Water::Water(int id) : id(id) {}

RigidBody* Water::getBody() {
    return body;
}

void Water::setBody(RigidBody* newBody) {
    body = newBody;
}

int Water::getID() const {
    return id;
}

void Water::customCollision(ICustomPhysics* otherObject) {
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
    playerBody.setPosition(config::SWAMP_RESPAWN + config::SWAMP_ROOM_POSITION);
    playerPtr->setJumpSfxCooldown(false);
}
