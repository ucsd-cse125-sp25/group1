#include "components/lilypad.hpp"
#include "config.hpp"
#include "player.hpp"
#include "server.hpp"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

LilyPad::LilyPad(int id, bool isGood, const glm::vec3& position, const glm::vec3& direction, Server& serverRef)
    : 
    lilyPadID(id),
    isGood(isGood),
    body(
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        0.0f, // mass of 0 - kinematics doesn't matter because it's static (imovable)
        new Transform { position, direction },
        new BoxCollider{
            isGood ? AABB : NONE, //TODO: change this to a nothing collider that just calls customCollision when coliding.
            glm::vec3(-config::SWAMP_LILYPAD_WIDTH / 2, -config::SWAMP_LILYPAD_HEIGHT / 2, -config::SWAMP_LILYPAD_WIDTH / 2),
            glm::vec3(config::SWAMP_LILYPAD_WIDTH / 2, config::SWAMP_LILYPAD_HEIGHT / 2, config::SWAMP_LILYPAD_WIDTH / 2)
        },
        this, // refernce to interface
        true
    ), 
    server(serverRef){}
//player position relative to room will this impact collision?

RigidBody& LilyPad::getBody() {
    return body;
}

int LilyPad::getID() const {
    return lilyPadID;
}

bool LilyPad::isGoodLilyPad() const {
    return isGood;
}

void LilyPad::customCollision(ICustomPhysics* otherObject) {
    // Good lilypad: normal collision
    if(isGood){
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