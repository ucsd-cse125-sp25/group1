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
    * @param numPads The number of pads in the swamp game.
    * @param audioFile The audio file associated with the swamp game.
    *
    */
    Swamp(int roomID, int numPads, std::string audioFile);

    /**
    * @brief Destructor for the Swamp class
    */
    ~Swamp();

private:
    int numPads;
    std::string audioFile;

};