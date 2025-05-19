#include "server.hpp"
#include "swamp.hpp"
#include "config.hpp"
#include <iostream>
#include "json.hpp"



using json = nlohmann::json;

Swamp::Swamp(int roomID, World& worldRef, Server& serverRef) : Room(roomID, "Swamp"), world(worldRef), server(serverRef) {

    numPads = config::SWAMP_NUM_PADS; //number of pads in the swamp game

    //TODO: Pull this from config?
    solution = config::SWAMP_SOLUTION;
    audioFile = config::SWAMP_AUDIO_FILE;

    respawnPoint = config::SWAMP_RESPAWN;

    // Initialize the lily pads
    pads.resize(numPads);
    for (int i = 0; i < numPads; i++) {
        for (int j = 0; j < 2; j++) {
            pads[i][j] = new LilyPad(
                i * 2 + j, // ID
                solution[i] == j, // Is good or bad
                config::SWAMP_LILYPAD_POS[i][j], //Position
                config::SWAMP_LILYPAD_DIR, //Direction
                server                     // Reference to the server
            );

            world.addObject(&(pads[i][j]->getBody()));
        }
    }

    // Initialize the frogs
    frogs.resize(config::SWAMP_NUM_FROGS);
    for (int i = 0; i < config::SWAMP_NUM_FROGS; i++) {

        //TODO Use this when new itneractable is in
        frogs[i] = new Frog(i,                 // ID
                                    config::SWAMP_FROG_POS[i], // Position
                                    config::SWAMP_FROG_DIR,    // Direction
                                    config::SWAMP_FROG_WIDTH,  // Width
                                    config::SWAMP_FROG_HEIGHT // Height
        );

        // TODO uncomment when new interactable is in
        //world.addObject(frogs[i]);
    }
}

Swamp::~Swamp() {
    // Destructor
    for (int i = 0; i < numPads; i++) {
        for (int j = 0; j < 2; j++) {
            delete pads[i][j];
        }
    }

    for (int i = 0; i < config::SWAMP_NUM_FROGS; i++) {
        delete frogs[i];
    }
}

std::string Swamp::getInitInfo() {
    // Return the initial information for the swamp game
    json initInfo;

    initInfo["type"] = "swamp_init";
    initInfo["room_ID"] = getID();
    initInfo["num_pads"] = numPads;
    initInfo["audio_file"] = audioFile;

    std::string packet = initInfo.dump() + "\n";
    return packet;
}


glm::vec3 Swamp::getRespawnPoint() {
    return respawnPoint;
}
