#pragma once

#include <glm/glm.hpp>
#include <array>
#include <utility>
#include <vector>
#include "collider.hpp"
#include "components/object.hpp"
#include "components/room.hpp"
#include "rigidBody.hpp"
#include "world.hpp"

class Server;
class World;

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

    void fireCannons();

  private:
    /**
     * @brief Number of walls in the circus game
     *
     * incremented as walls created to reach the total number of walls
     */
    int numWalls;

    /**
     * @brief List of lily pads in the swamp game
     *
     * A vector of pointers to lilypad. Lilypadd ordering goes right, left, right, left...
     */
    std::vector<Object*> walls;

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
