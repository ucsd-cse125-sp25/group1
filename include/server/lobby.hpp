#pragma once

#include <glm/glm.hpp>
#include <array>
#include <utility>
#include <vector>
#include "collider.hpp"
#include "components/finalButton.hpp"
#include "components/finalDoor.hpp"
#include "components/object.hpp"
#include "components/room.hpp"
#include "rigidBody.hpp"
#include "world.hpp"

class Server;

class Lobby : public Room {
  public:
    /**
     * @brief Constructs a Lobby instance.
     *
     * Initializes the Lobby
     */
    Lobby(int roomID, World& worldRef, Server& serverRef);

    /**
     * @brief Destructor for Lobby.
     */
    ~Lobby();

    /**
     * @brief Returns the game initialization information client side needs in a packet
     *
     * @return A JSON string containing the game initialization information.
     *
     * Example JSON:
     * {
     *     "type": "lobby_init",
     *     "room_ID": 5,
     * }
     */
    std::string getInitInfo();

    /**
     * @brief Returns references  to the server
     * @return Server&
     */
    Server& getServer();

    /**
     * Used for initBodies 
     * @brief instantiates a FinalDoor object
     */
    FinalDoor* createFinalDoor(int objectID);

    /**
     * Used for initBodies
     * @brief instantiates a FinalButton object
     */
    FinalButton* createFinalButton(int objectID);

    int playerID; // Unique ID for the player in the lobby

    /**
     * @brief Audio file for the lobby
     *
     * The audio file to be played for when they are in the lobby
     */
    std::string audioFile;

    /**
     * @brief Reference to the world object
     *
     */
    World& world;

    /**
     * @brief Reference to the server object
     */
    Server& server;

    /**
     * @brief List of buttons
     *
     * A vector of pointers to lilypad. Lilypadd ordering goes right, left, right, left...
     */
    std::vector<FinalButton*> buttons;

    FinalDoor* finalDoor; // Pointer to the final door in the lobby
};
