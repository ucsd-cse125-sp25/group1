#pragma once

#include <glm/glm.hpp>
#include <array>
#include <utility>
#include <vector>
#include "collider.hpp"
#include "components/object.hpp"
#include "components/pianoKey.hpp"
#include "components/pianoRespawn.hpp"
#include "components/room.hpp"
#include "rigidBody.hpp"
#include "world.hpp"

class Server;

class Piano : public Room {
  public:
    /**
     * @brief Constructs a Piano instance.
     *
     * Initializes the Piano
     */
    Piano(int roomID, World& worldRef, Server& serverRef);

    /**
     * @brief Destructor for Piano.
     */
    ~Piano();

    /**
     * @brief Initializes the water plane that respawns players upon contact.
     *
     * Note: the setBody() method must be called on the returned Water instance.
     *
     */
    PianoRespawn* createRespawn();

    /**
     * @brief Returns references  to the server
     * @return Server&
     */
    Server& getServer();

    // std::array<bool, 14> pressedNotes = {false};
    PianoKey* createPianoKey();

    int getPlayedIndex();

    void setPlayedIndex(int index);

    int getSolutionNote(int index);

  private:
    /**
     *  @brief Solution Key to the Swamp Game
     *
     * A vector, where each element is 0 or 1 representing, the correct lilpad for that step [index]
     * 0: right lilypad, 1: left lilypad
     */
    std::array<int, 14> solution;

    PianoRespawn* respawn = nullptr;
    /**
     * @brief Reference to the world object
     *
     */
    World& world;

    Server& server;

    int numKeys = 0; // Number of piano keys created

    std::vector<PianoKey*> keys; // List of piano keys in the room

    int playedIndex = 0;
};
