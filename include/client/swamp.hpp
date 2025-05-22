#pragma once

#include <array>
#include <vector>
#include "components/room.hpp"

class Swamp : public Room {
  public:
    /**
     * @brief Constructor for the Swamp class
     *
     * @param roomID The ID of the room.
     * @param audioFile The audio file associated with the swamp game.
     *
     */
    Swamp(int roomID, std::string audioFile);

    /**
     * @brief Destructor for the Swamp class
     */
    ~Swamp();

  private:
    std::string audioFile;
};
