#pragma once

#include <glm/glm.hpp>
#include <array>
#include <utility>
#include <vector>
#include "collider.hpp"
#include "components/lilypad.hpp"
#include "components/object.hpp"
#include "components/room.hpp"
#include "rigidBody.hpp"
#include "world.hpp"

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
     *     "audio_file": "swamp_audio.mp3"
     *     "audio_file": "swamp_audio.mp3"
     * }
     */
    std::string getInitInfo();

    glm::vec3 getRespawnPoint();

    std::pair<LilyPad*, ColliderType> createLilyPad();

  private:
    /**
     * @brief Number of pads in the swamp game
     *
     * incremented as lilypads created to reach the total number of pads
     */
    int numPads;

    /**
     * @brief List of lily pads in the swamp game
     *
     * A vector of pointers to lilypad. Lilypadd ordering goes right, left, right, left...
     */
    std::vector<LilyPad*> pads;

    /**
     *  @brief Solution Key to the Swamp Game
     *
     * A vector, where each element is 0 or 1 representing, the correct lilpad for that step [index]
     * 0: right lilypad, 1: left lilypad
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