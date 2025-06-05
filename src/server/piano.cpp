#include "piano.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Piano::Piano(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "pianoRoom"), world(worldRef), server(serverRef) {

    // solution = config::PIANO_SOLUTION;
}

Piano::~Piano() {
    // Destructor
    delete respawn;
}

PianoRespawn* Piano::createRespawn() {
    int id = 0;
    respawn = new PianoRespawn(id);
    return respawn;
}

Server& Piano::getServer() {
    return server;
}
