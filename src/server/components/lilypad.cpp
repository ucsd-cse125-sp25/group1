#include "components/lilypad.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "player.hpp"
#include "server.hpp"

using json = nlohmann::json;

LilyPad::LilyPad(int id, bool isGood, Server& serverRef)
    : lilyPadID(id), isGood(isGood), server(serverRef) {}
// player position relative to room will this impact collision?

RigidBody* LilyPad::getBody() {
    return body;
}

void LilyPad::setBody(RigidBody* newBody) {
    body = newBody;
}

int LilyPad::getID() const {
    return lilyPadID;
}

bool LilyPad::isGoodLilyPad() const {
    return isGood;
}

void LilyPad::customCollision(ICustomPhysics* otherObject) {
    // Good lilypad: normal collision
    if (isGood) {
        return;
    }
    // Bad lilypad: dunk player and respawn them
    Player* playerPtr = dynamic_cast<Player*>(otherObject);
    // make sure it's a player that hit the lilypad
    if (!playerPtr) {
        return;
    }

    // Send Message to client to drop lily pad
    json message;
    message["type"] = "lilypad_drop";
    message["id"] = lilyPadID;

    std::string packet = message.dump() + "\n";
    server.broadcastMessage(packet);

    std::cout << "Lilypad " << lilyPadID << " dropped" << std::endl;

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