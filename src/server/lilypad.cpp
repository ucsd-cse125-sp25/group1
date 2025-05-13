#include "lilypad.hpp"
#include "config.hpp"
#include "player.hpp"

LilyPad::LilyPad(int id, bool isGood, const glm::vec3& position, const glm::vec3& direction)
    : 
    lilyPadID(id),
    isGood(isGood),
    body(
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        0.0f, // mass of 0 - kinematics doesn't matter because it's static (imovable)
        new Transform { position, direction },
        new BoxCollider{
            AABB, //TODO: change this to a nothing collider that just calls customCollision when coliding.
            glm::vec3(-config::SWAMP_LILYPAD_WIDTH / 2, -config::SWAMP_LILYPAD_HEIGHT / 2, -config::SWAMP_LILYPAD_WIDTH / 2),
            glm::vec3(config::SWAMP_LILYPAD_WIDTH / 2, config::SWAMP_LILYPAD_HEIGHT / 2, config::SWAMP_LILYPAD_WIDTH / 2)
        },
        this, // refernce to interface
        true
    ) {}

RigidBody& LilyPad::getBody() {
    return body;
}

void LilyPad::customCollision(ICustomPhysics* otherObject) {
    // Good lilypad: normal collision
    if(isGood){
        return;
    }
    // Bad lilypad: dunk player and respawn them.
    Player* playerPtr = dynamic_cast<Player*>(otherObject);
    // make sure it's a player that hit the lilypad
    if (!playerPtr) {
        return;
    }
    // TODO: call server.broadcastMessage(packet) to let the client know to stop rendering this lilypad.

    /*
    TODO: move the following logic to the lower layer water rigidbody, rather than the lilypad.
    This way, the player falls all the way through the lilypad, goes underwater, and then respawns.
    */ 
    // respawn player at the spawn point
    RigidBody& body = playerPtr->getBody();
    // Make sure the player has no residual movement on respawn
    body.setForce(glm::vec3{0.0f, 0.0f, 0.0f});
    body.setVelocity(config::SWAMP_RESPAWN);
    // TODO: add offset for the individual player, so 2 players don't spawn into the same spot.
    body.setPosition(config::SWAMP_RESPAWN);
}