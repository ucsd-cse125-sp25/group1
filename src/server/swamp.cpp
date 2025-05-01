#include "server.hpp"
#include "swamp.hpp"
#include "config.hpp"
#include <iostream>
#include "json.hpp"


using json = nlohmann::json;

Swamp::Swamp(int roomID) : Room(roomID, "Swamp") {

    numPads = 10; //number of pads in the swamp game

    gameState = std::vector<std::array<int, 2>>(numPads, { 1, 1 });

    //TODO: Pull this from config?
    soluiton = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };
    audioFile = "solution_audio.mp3";

    respawnPoint = config::SWAMP_RESPAWN;
}

Swamp::~Swamp() {
    // Destructor
}

bool Swamp::init() {
    // Initialize the swamp game


    //Create instances of the pads

    //send soluton audio file to frog? (or on client side)
    // frog interact is audio only if audio only played on interacting client do we need frog on our side?  audio solution present in game init. 

    std::cout << "Swamp Initialized \n" << std::endl;
    return true;
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