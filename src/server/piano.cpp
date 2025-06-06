#include "piano.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Piano::Piano(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "pianoRoom"), world(worldRef), server(serverRef) {

    solution = config::PIANO_SOLUTION;
}

Piano::~Piano() {
    // Destructor
    for (auto& key : keys) {
        delete key;
    }
    delete respawn;
}

PianoRespawn* Piano::createRespawn() {
    int id = 0;
    respawn = new PianoRespawn(id, this);
    return respawn;
}

Server& Piano::getServer() {
    return server;
}

PianoKey* Piano::createPianoKey() {
    PianoKey* newKey = new PianoKey(numKeys, config::K_CONSTANT, config::DAMP_FACTOR,
                                    glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f), server, this);

    numKeys++;
    return newKey;
}

int Piano::getPlayedIndex() {
    return playedIndex;
}

void Piano::setPlayedIndex(int index) {
    playedIndex = index;
}

int Piano::getSolutionNote(int index) {
    return solution[index];
}
