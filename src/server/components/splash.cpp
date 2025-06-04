#include "components/splash.hpp"
#include <iostream>
#include "json.hpp"
#include "player.hpp"
#include "server.hpp"

using json = nlohmann::json;

Splash::Splash(int id, Server& serverRef) : Object(id), server(serverRef) {}

void Splash::customCollision(ICustomPhysics* otherObject) {
    auto* playerPtr = dynamic_cast<Player*>(otherObject);
    // make sure it's a player that hit the water plane
    if (!playerPtr) {
        return;
    }
    
    json sfx;
    sfx["type"] = "sfx";
    sfx["sfx_id"] = config::WATERSPLASH;
    sfx["client_id"] = playerPtr->getID();
    sfx["action"] = "jump";
    sfx["volume"] = config::WATERSPLASH_VOL;

    std::string sfxPacket = sfx.dump() + "\n";
    server.broadcastMessage(sfxPacket);
}
