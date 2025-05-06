#include "swamp.hpp"
#include <iostream>


void printGameState(const std::vector<std::array<int, 2>>& gameState) {
    for (const auto& arr : gameState) {
        std::cout << "[" << arr[0] << ", " << arr[1] << "] ";
    }
    std::cout << std::endl;
}

Swamp::Swamp(int roomID, std::vector<std::array<int, 2>> gameState, int numPads, std::string audioFile)
    : Room(roomID), gameState(gameState), numPads(numPads), audioFile(audioFile) {
    std::cout << "Swamp constructor \n" << std::endl;

    //TODO: For the lilypad positions , should it be the same or different from the server? and the one in config

    // Set up the frogs. 
    printGameState(gameState);
}

Swamp::~Swamp() {
    // Destructor
    std::cout << "Swamp Room destructor \n" << std::endl;
}

std::vector<std::array<int, 2>> Swamp::getGameState() {
    return gameState;
}

void Swamp::setGameState(std::vector<std::array<int, 2>> newGameState) {
    gameState = newGameState;
}

// only the person that presses e on the frog hears the audio (then server doesn't need to know)