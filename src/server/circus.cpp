#include "circus.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Circus::Circus(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "Circus"), world(worldRef), server(serverRef), respawnCreated(false) {
    respawnPoint = config::CIRCUS_RESPAWN + config::CIRCUS_ROOM_POSITION;
    numWalls = 0;       // numWalls is incremented as createWall is called
    numCannonballs = 0; // numCannonballs is incremented as createCannonball is called
    cannonTimerActive = false;
    cannonTicksRemaining = 0;
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

CircusRespawn* Circus::createRespawn() {
    respawnCreated = true;
    CircusRespawn* respawn = new CircusRespawn(0, server);
    return respawn;
}

bool Circus::isRespawnCreated() const {
    return respawnCreated;
}

void Circus::stopMusicMessage() {
    json message;
    message["type"] = "pause_circus_music";

    std::string packet = message.dump() + "\n";
    server.broadcastMessage(packet);
    // start a timer (3 seconds). Once it hits zero, shoot cannonballs.
    cannonTimerActive = true;
    cannonTicksRemaining = config::SECONDS_CANNON_DELAY * (1000 / config::TICK_RATE);
}

void Circus::cannonLoop() {
    if (!cannonTimerActive && !cannonsFiring) {
        cannonTimerActive = true;
        cannonTicksRemaining = config::SECONDS_CANNON_DELAY * (1000 / config::TICK_RATE);
    }
    // If cannons are firing, broadcast positions. Otherwise, count down timer
    broadcastCannonballPositions();
}

void Circus::fireCannons() {
    for (Cannonball* cannonball : cannonballs) {
        cannonball->fire();
    }
    cannonsFiring = true;
}

void Circus::broadcastCannonballPositions() {
    if (cannonTimerActive) {
        if (cannonTicksRemaining <= 0) {
            fireCannons();
            cannonTimerActive = false;
        } else {
            cannonTicksRemaining--;
        }
    }
    // Don't do anything if cannons aren't firing
    if (!cannonsFiring) {
        return;
    }
    // Cannonballs are flying
    json message;
    message["type"] = "cannonball_positions";
    for (Cannonball* cannonball : cannonballs) {
        glm::vec3 position = cannonball->getBody()->getPosition();
        // indicate where the current cannonball is
        json entry;
        entry["id"] = cannonball->getID();
        entry["position"] = {position.x, position.y, position.z};
        message["cannonballs"].push_back(entry);
    }
    std::string packet = message.dump() + "\n";
    server.broadcastMessage(packet);

    // potentially update cannonsFiring to false
    cannonsFiring = false;
    for (Cannonball* cannonball : cannonballs) {
        if (cannonball->getBody()->getVelocity() != glm::vec3(0.0f, 0.0f, 0.0f)) {
            cannonsFiring = true;
        }
    }
}
