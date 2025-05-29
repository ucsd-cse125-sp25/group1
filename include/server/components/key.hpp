#pragma once
#include <glm/glm.hpp>
#include <string>
#include "rigidBody.hpp"
#include "server.hpp"
#include "world.hpp"

class Server;
class World;

class Key : public Object {
  public:
    /**
     * @brief Constructs a Key object with a given ID and room name.
     *
     * @param id The unique identifier for the key.
     * @param room The name of the room where the key is located.
     * @param serverRef Reference to the Server instance for broadcasting messages.
     * @param worldRef Reference to the physics world instance for removing its rigidBody.
     */
    Key(int id, std::string room, Server& serverRef, World& worldRef);

    ~Key() = default;

    /**
     * @brief custom collision response of lilypad
     *
     * @param ptr to the object class that this object collided with
     */
    void customCollision(ICustomPhysics* otherObject) override;

  private:
    std::string roomName;
    RigidBody* body = nullptr;
    Server& server;
    World& world;
};
