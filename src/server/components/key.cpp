#include "components/key.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "player.hpp"
#include "server.hpp"

using json = nlohmann::json;

Key::Key(int id, std::string room, Server& serverRef, World& worldRef)
    : Object(id), roomName(room), server(serverRef), world(worldRef) {}
// player position relative to room will this impact collision?

void Key::customCollision(ICustomPhysics* otherObject) {

    // Collision response for Key
    Player* playerPtr = dynamic_cast<Player*>(otherObject);
    if (!playerPtr) {
        std::cerr << "Key collided with non-player object." << std::endl;
        return;
    }

    json message;
    message["type"] = "key_pickup";
    message["room"] = roomName;
    message["id"] = this->getID();
    playerPtr->addKey(this->getID());

    std::string packet = message.dump() + "\n";
    server.broadcastMessage(packet);

    world.removeObject(this->getBody());
}
