#include "components/key.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "player.hpp"
#include "server.hpp"

using json = nlohmann::json;

Key::Key(int id, std::string room, Server& serverRef)
    : keyID(id), roomName(room), server(serverRef) {}
// player position relative to room will this impact collision?

RigidBody* Key::getBody() {
    return body;
}

void Key::setBody(RigidBody* newBody) {
    body = newBody;
}

int Key::getID() const {
    return keyID;
}

std::string Key::getRoomName() const {
    return roomName;
}

void Key::customCollision(ICustomPhysics* otherObject) {

    // Collision response for Key
    Player* playerPtr = dynamic_cast<Player*>(otherObject);
    if (!playerPtr) {
        return;
    }

    json message;
    message["type"] = "key_pickup";
    message["room_name"] = roomName; // Room where the key is located
    message["id"] = keyID;
    playerPtr->addKey(keyID);

    std::string packet = message.dump() + "\n";
    server.broadcastMessage(packet);

}
