#include "swamp.hpp"
#include <iostream>

Swamp::Swamp(int roomID, std::vector<std::array<int, 2>> gameState, int numPads, std::string audioFile)
	: Room(roomID), gameState(gameState), numPads(numPads), audioFile(audioFile) {

	std::cout << "Swamp Room constructor \n" << std::endl;
	for (const auto& arr : gameState) {
		std::cout << "[";
		for (size_t i = 0; i < arr.size(); ++i) {
			std::cout << arr[i];
			if (i < arr.size() - 1) std::cout << ", ";
		}
		std::cout << "] ";
	}
	std::cout << std::endl;
}

Swamp::getGameState() {
	return gameState;
}