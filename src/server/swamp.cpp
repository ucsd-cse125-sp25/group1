#include "server.hpp"
#include "swamp.hpp"
#include <iostream>
#include "json.hpp"


using json = nlohmann::json;

Swamp::Swamp(int roomID) : Room(roomID, "Swamp") {

	numPads = 10; //number of pads in the swamp game

	gameState = std::vector<std::array<int, 2>>(numPads, { 1, 1 });

	soluiton = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };
	//move solution over to config
	// mapp solution id to object id. 

}

Swamp::~Swamp() {
	// Destructor
}

bool Swamp::init() {
	// Initialize the swamp game


	//Create instances of the pads

	//determine the solution 

	std::cout << "Swamp Initialized \n" << std::endl;
	return true;
}

std::string Swamp::getInitInfo() {
	// Return the initial information for the swamp game
	json initInfo;

	initInfo["type"] = "swampInit";
	initInfo["roomID"] = getID();
	initInfo["numPads"] = numPads;
	initInfo["gameState"] = gameState;
	initInfo["audioFile"] = "swamp_audio.mp3";

	std::string packet = initInfo.dump() + "\n";
	return packet;
}


std::vector<std::array<int, 2>> Swamp::getGameState() {
	// Return the current game state
	return gameState;
}