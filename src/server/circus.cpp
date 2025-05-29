#include "circus.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Circus::Circus(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "Swamp"), world(worldRef), server(serverRef), numWalls(0),
      respawnPoint(config::CIRCUS_RESPAWN) {}

Circus::~Circus() {
    // Destructor
    for (int i = 0; i < numWalls; i++) {
        delete walls[i];
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

void stopMusicMessage() {
    json message;
    message["type"] = "stop_music";

    return message;
}

void fireCannons() {
    for (CannonBall* cannonBall : cannonBalls) {
        RigidBody* cannonBallBody = cannonBall->getBody();
        cannonBallBody.setVelocity(/*TODO*/);
    }
}
