#include "swamp.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Swamp::Swamp(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "Swamp"), world(worldRef), server(serverRef) {

    numPads = 0; // config::SWAMP_NUM_LILYPADS; // number of pads in the swamp game

    // TODO: Pull this from config?
    solution = config::SWAMP_SOLUTION;
    audioFile = config::SWAMP_AUDIO_FILE;

    respawnPoint = config::SWAMP_RESPAWN;

    // Initialize the lily pads
    // pads.resize(config::SWAMP_NUM_ROWS);
    // for (int i = 0; i < numPads; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         pads[i][j] = new LilyPad(i * 2 + j,                       // ID
    //                                  solution[i] == j,                // Is good or bad
    //                                  config::SWAMP_LILYPAD_POS[i][j], // Position
    //                                  config::SWAMP_LILYPAD_DIR,       // Direction
    //                                  server                           // Reference to the server
    //         );

    //        world.addObject(&(pads[i][j]->getBody()));
    //    }
    //}
}

Swamp::~Swamp() {
    // Destructor
    for (int i = 0; i < numPads; i++) {
            delete pads[i];
    }
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
    bool isGood = solution[id / 2] == 1;
    ColliderType colliderType = isGood ? AABB : NONE;
    LilyPad* newPad = new LilyPad(id, isGood, server);
    pads.push_back(newPad);

    numPads++;

    return std::make_pair(newPad, colliderType);
}