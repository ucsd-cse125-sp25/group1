#pragma once

#include <glm/glm.hpp>
#include <array>
#include <utility>
#include <vector>
#include "collider.hpp"
#include "components/cannonball.hpp"
#include "components/object.hpp"
#include "components/room.hpp"
#include "rigidBody.hpp"
#include "server.hpp"
#include "world.hpp"

class Server;
class World;
// class Cannonball;

class Circus : public Room {
  public:
    /**
     * @brief Constructs a Circus instance.
     *
     * Initializes the Circus
     */
    Circus(int roomID, World& worldRef, Server& serverRef);

    /**
     * @brief Destructor for Circus.
     */
    ~Circus();

    /**
     * @brief Returns the game initialization information client side needs in a packet
     *
     * @return A JSON string containing the game initialization information.
     *
     * Example JSON:
     * {
     *     "type": "circus_init",
     *     "room_ID": 2,
     * }
     */
    std::string getInitInfo();

    glm::vec3 getRespawnPoint();

    Object* createWall();

    Cannonball* createCannonball(glm::vec3 cannonPosition);

    /**
     * @brief send a message to the client to stop the music
     */
    void stopMusicMessage();

    void fireCannons();

  private:
    /**
     * @brief Number of walls in the circus game
     *
     * incremented as walls created to reach the total number of walls
     */
    int numWalls;

    /**
     * @brief Number of cannonballs in the circus game
     *
     * incremented as cannonballs created to reach the total number of cannonballs
     */
    int numCannonballs;

    /**
     * @brief List of walls in the circus game
     *
     * A vector of pointers to Objects (walls).
     */
    std::vector<Object*> walls;

    /**
     * @brief List of cannonballs in the circus game
     *
     * A vector of pointers to Cannonballs. Used for firing logic.
     */
    std::vector<Cannonball*> cannonballs;

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

    /**
     * @brief Reference to the server
     *
     */
    Server& server;
};
