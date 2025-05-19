#pragma once

#include <vector>
#include <array>
#include "components/room.hpp"
#include "components/object.hpp"
#include "components/lilypad.hpp"
#include "components/frog.hpp"
#include "world.hpp"
#include <glm/glm.hpp>

class Server;


class Swamp : public Room {
public:
    /**
    * @brief Constructs a Swamp instance.
    *
    * Initializes the swamp
    */
    Swamp(int roomID, World& worldRef, Server& serverRef);

    /**
     * @brief Destructor for Swamp.
     */
    ~Swamp();

    /**
     * @brief Returns the game initialization information client side needs in a packet
     *
     * @return A JSON string containing the game initialization information.
     *
     * Example JSON:
     * {
     *     "type": "swamp_init",
     *     "room_ID": 1,
     *     "num_pads": 4,
     *     "game_state": {{1,1},{1,1},{1,1},{1,1}}
     *     "audio_file": "swamp_audio.mp3"
     * }
     */
    std::string getInitInfo();

    glm::vec3 getRespawnPoint();

private:
    /**
     * @brief Number of pads in the swamp game
     */
    int numPads;

    
    /**
    * @brief List of lily pads in the swamp game
    *
    * A vector of pairs, each element is a pair of pointers to the two lilypads that are part of the same step.
    */
    std::vector<std::array<LilyPad*, 2>> pads;

    /**
     *
     *@brief list of the frogs that are interactable in swamp game
     */
    std::vector<Frog*> frogs;


    /**
      *  @brief Solution Key to the Swamp Game
      *
      * A vector, where each element is 0 or 1 representing, the correct lilpad for that step [index] .
      */
    std::vector<int> solution;

    /**
     * @brief Audio file for the swamp game
     *
     * The audio file to be played during the swamp game.
     */
    std::string audioFile;


    /**
     * @brief Respawn Point in Swamp Game when player dies
     *
     */
    glm::vec3 respawnPoint;

    /**
     * @brief Reference to the world object
     * 
     */
    World& world;

    Server& server;
};