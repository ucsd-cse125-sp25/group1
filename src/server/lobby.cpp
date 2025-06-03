#include "lobby.hpp"
#include <iostream>
#include "config.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

Lobby::Lobby(int roomID, World& worldRef, Server& serverRef)
    : Room(roomID, "Lobby"), world(worldRef), server(serverRef) {
}

Lobby::~Lobby() {
  
}

std::string Lobby::getInitInfo() {
    // Return the initial information for the swamp game
    json initInfo;

    initInfo["type"] = "swamp_init";
    initInfo["room_ID"] = getID();
    initInfo["audio_file"] = audioFile;

    std::string packet = initInfo.dump() + "\n";
    return packet;
}

FinalDoor* Lobby::createFinalDoor(int numKeys) {
    FinalDoor* door = new FinalDoor(numKeys, this);
    addInteractable(std::unique_ptr<FinalDoor>(door));
    return door;
}

FinalButton* Lobby::createFinalButton(int buttonID, int playerID) {
    FinalButton* button = new FinalButton(buttonID, playerID, finalDoor);
    addInteractable(std::unique_ptr<FinalButton>(button));
    return button;
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

Server& Lobby::getServer() {
    return server;
}
