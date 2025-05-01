#pragma once

#include <vector>
#include <array>
#include "components/room.hpp"

class Swamp : public Room {
public:
    /**
    * @brief Constructor for the Swamp class
    *
    * @param roomID The ID of the room.
    * @param gameState A vector of pairs representing the game state of the swamp game.
    * @param numPads The number of pads in the swamp game.
    * @param audioFile The audio file associated with the swamp game.
    *
    */
    Swamp(int roomID, std::vector<std::array<int, 2>> gameState, int numPads, std::string audioFile);

    /**
    * @brief Destructor for the Swamp class
    */
    ~Swamp();

    /**
    * @brief The game state of the swamp game
    *
    * @return A vector of pairs representing the game state of the swamp game.
    */
    std::vector<std::array<int, 2>> getGameState();

    /**
     * @brief Set game state
     *
     * @param A vectory of pairs representing the new game state
     */
    void setGameState(std::vector<std::array<int, 2>> newGameState);

private:
    std::vector<std::array<int, 2>> gameState;
    int numPads;
    std::string audioFile;

};