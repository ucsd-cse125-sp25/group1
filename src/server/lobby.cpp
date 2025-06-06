#include "lobby.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Lobby::Lobby(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "Lobby"), world(worldRef), server(serverRef) {
    playerID = 0; // Initialize playerID to 0, this will increment as players join
}

Lobby::~Lobby() {}

std::string Lobby::getInitInfo() {
    // Return the initial information for the swamp game
    json initInfo;

    initInfo["type"] = "swamp_init";
    initInfo["room_ID"] = getID();
    initInfo["audio_file"] = audioFile;

    std::string packet = initInfo.dump() + "\n";
    return packet;
}

FinalDoor* Lobby::createFinalDoor(int objectID) {
    int numKeys = 2;
    FinalDoor* door = new FinalDoor(numKeys, objectID, this);
    std::cout << "Creating FinalDoor with ID: " << objectID << std::endl;
    finalDoor = door;
    addInteractable(door);
    return door;
}

FinalButton* Lobby::createFinalButton(int buttonID) {
    FinalButton* button = new FinalButton(buttonID, playerID, finalDoor);
    playerID++; // Increment playerID for the next button
    buttons.push_back(button);
    addInteractable(button);
    return button;
}

Server& Lobby::getServer() {
    return server;
}
