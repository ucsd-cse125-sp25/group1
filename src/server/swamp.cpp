#include "swamp.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Swamp::Swamp(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "Swamp"), world(worldRef), server(serverRef) {

    numPads = 0;

    solution = config::SWAMP_SOLUTION;
    audioFile = config::SWAMP_AUDIO_FILE;

    respawnPoint = config::SWAMP_RESPAWN;
}

Swamp::~Swamp() {
    // Destructor
    for (int i = 0; i < numPads; i++) {
        delete pads[i];
    }
    delete waterRespawnPlane;
}

std::string Swamp::getInitInfo() {
    // Return the initial information for the swamp game
    json initInfo;

    initInfo["type"] = "swamp_init";
    initInfo["room_ID"] = getID();
    initInfo["audio_file"] = audioFile;

    std::string packet = initInfo.dump() + "\n";
    return packet;
}

glm::vec3 Swamp::getRespawnPoint() {
    return respawnPoint;
}

std::pair<LilyPad*, ColliderType> Swamp::createLilyPad() {
    int id = numPads;
    bool isGood = solution[id / 2] == id % 2;

    ColliderType colliderType = isGood ? AABB : NONE;
    LilyPad* newPad = new LilyPad(id, isGood, server);

    pads.push_back(newPad);

    numPads++;

    return std::make_pair(newPad, colliderType);
}

Water* Swamp::createWaterRespawn() {
    int id = 0;
    waterRespawnPlane = new Water(id, server);
    return waterRespawnPlane;
}
