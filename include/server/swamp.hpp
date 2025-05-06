#pragma once

#include <vector>
#include <array>
#include "components/room.hpp"
#include "components/interactable.hpp"
#include "components/object.hpp"
#include "world.hpp"
#include <glm/glm.hpp>


class Swamp : public Room {
public:
    /**
    * @brief Constructs a Swamp instance.
    *
    * Initializes the swamp
    */
    Swamp(int roomID, World& worldRef);

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


    /**
     * @brief The game state of the swamp game
     *
     * @return A vector of pairs representing the game state of the swamp game.
     */
    std::vector<std::array<int, 2>> getGameState();

    glm::vec3 getRespawnPoint();

    /**
     * @brief Returns the game state client side needs in a packet for update
     *
     * @return A JSON string containing the game state
     *
     * Example JSON:
     * {
     *     "type": "swamp_update",
     *     "game_state": {{1,1},{1,1},{1,1},{1,1}}
     * }
     */
    std::string getUpdatePacket();



private:
    /**
     * @brief Number of pads in the swamp game
     */
    int numPads;

    /**
     * @brief Current game state of the swamp game
     *
     * A vector of length numPads of pairs, each element is either 0 (lilypad has sunk) or 1 (lilypad is rendered).
     */
    std::vector<std::array<int, 2>> gameState;

    
    /**
    * @brief List of lily pads in the swamp game
    *
    * A vector of pairs, each element is a pair of pointers to the two lilypads that are part of the same step.
    */
    std::vector<std::array<Object*, 2>> pads;


    /**
      *  @brief Solution Key to the Swamp Game
      *
      * A vector, where each element is 0 or 1 representing, the correct lilpad for that step [index] .
      */
    std::vector<int> soluiton;

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
};