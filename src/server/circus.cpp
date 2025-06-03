#include "circus.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Circus::Circus(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "Circus"), world(worldRef), server(serverRef),
      respawnPoint(config::CIRCUS_RESPAWN) {
    numWalls = 0;       // numWalls is incremented as createWall is called
    numCannonballs = 0; // numCannonballs is incremented as createCannonball is called
}

Circus::~Circus() {
    // Destructor
    for (int i = 0; i < numWalls; i++) {
        delete walls[i];
    }

    for (int i = 0; i < numCannonballs; i++) {
        delete cannonballs[i];
    }
}

std::string Circus::getInitInfo() {
    // Return the initial information for the circus game
    json initInfo;
    initInfo["type"] = "circus_init";
    initInfo["room_ID"] = getID();

    std::string packet = initInfo.dump() + "\n";
    return packet;
}

glm::vec3 Circus::getRespawnPoint() {
    return respawnPoint;
}

Object* Circus::createWall() {
    int id = numWalls;
    Object* newWall = new Object(id);

    walls.push_back(newWall);
    numWalls++;

    return newWall;
}

Cannonball* Circus::createCannonball(glm::vec3 cannonPosition) {
    int id = numCannonballs;
    Cannonball* newCannonball = new Cannonball(id, cannonPosition);

    cannonballs.push_back(newCannonball);
    numCannonballs++;

    return newCannonball;
}

void Circus::stopMusicMessage() {
    json message;
    message["type"] = "pause_circus_music";
    server.broadcastMessage(message);
    // TODO: start a timer (3-4 seconds?). Once it hits zero, shoot cannonballs.
}

void Circus::fireCannons() {
    for (Cannonball* cannonball : cannonballs) {
        // TODO: think about how to hit all (or closest) players
        // cannonball->fire(server.getPlayers()[i]);
    }
}
