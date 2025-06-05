#pragma once

#include <array>
#include <vector>
#include "components/room.hpp"

class Circus : public Room {
  public:
    /**
     * @brief Constructor for the Circus class
     *
     * @param roomID The ID of the room.
     *
     */
    Circus(int roomID);

    /**
     * @brief Destructor for the Swamp class
     */
    ~Circus();

    /**
     * @brief stops the music for the current client. Called during red light green light
     */
    void stopMusic();
};
