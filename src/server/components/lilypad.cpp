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
    Player* playerPtr = dynamic_cast<Player*>(otherObject);
    // make sure it's a player that hit the lilypad
    if (!playerPtr) {
        return;
    }

    json sfx;
    sfx["type"] = "sfx";
    sfx["sfx_id"] = config::JUMPLILYPAD;
    sfx["client_id"] = playerPtr->getID();
    sfx["action"] = "jump";

    std::string sfxPacket = sfx.dump() + "\n";
    server.broadcastMessage(sfxPacket);

    // Good lilypad: normal collision
    if (isGood) {
        return;
    }

    // Send Message to client to drop lily pad
    json message;
    message["type"] = "lilypad_drop";
    message["id"] = lilyPadID;

    std::string packet = message.dump() + "\n";
    server.broadcastMessage(packet);

    // std::cout << "Lilypad " << lilyPadID << " dropped" << std::endl;
}
