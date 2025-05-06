#include "server.hpp"
#include "swamp.hpp"
#include "config.hpp"
#include <iostream>
#include "json.hpp"


using json = nlohmann::json;

Swamp::Swamp(int roomID, World& worldRef) : Room(roomID, "Swamp"), world(worldRef) {

    numPads = config::SWAMP_NUM_PADS; //number of pads in the swamp game

    gameState = std::vector<std::array<int, 2>>(numPads, { 1, 1 });

    //TODO: Pull this from config?
    soluiton = config::SWAMP_SOLUTION;
    audioFile = config::SWAMP_AUDIO_FILE;

    respawnPoint = config::SWAMP_RESPAWN;

    // Initialize the lily pads
    pads.resize(numPads);
    for (int i = 0; i < numPads; i++) {
        for (int j = 0; j < 2; j++) {
            pads[i][j] = new Object(
                i * 2 + j, // ID
                config::SWAMP_LILYPAD_POS[i][j], //Position
                config::SWAMP_LILYPAD_DIR[i][j], //Direction
                config::SWAMP_LILYPAD_WIDTH, //Width
                config::SWAMP_LILYPAD_HEIGHT //Height
            );

            world.addObject(&(pads[i][j]->getBody()));
            
        }
    }
}

Swamp::~Swamp() {
    // Destructor
    for (int i = 0; i < numPads; i++) {
        for (int j = 0; j < 2; j++) {
            delete pads[i][j];
        }
    }
}

std::string Swamp::getInitInfo() {
    // Return the initial information for the swamp game
    json initInfo;

    initInfo["type"] = "swamp_init";
    initInfo["room_ID"] = getID();
    initInfo["num_pads"] = numPads;
    initInfo["game_state"] = gameState;
    initInfo["audio_file"] = audioFile;

    std::string packet = initInfo.dump() + "\n";
    return packet;
}


std::vector<std::array<int, 2>> Swamp::getGameState() {
    // Return the current game state
    return gameState;
}

glm::vec3 Swamp::getRespawnPoint() {
    return respawnPoint;
}

std::string Swamp::getUpdatePacket() {
    json updateInfo;

    updateInfo["type"] = "swamp_update";
    updateInfo["game_state"] = gameState;

    std::string packet = updateInfo.dump() + "\n";
    return packet;
}