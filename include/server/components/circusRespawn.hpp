#pragma once
#include "components/object.hpp"

class ICustomPhysics;
class Server;

class CircusRespawn : public Object {
  public:
    /**
     * @brief Constructs a CircusRespawn plane with the given id for water player respawn
     *
     * The circus floor plane is a rigidbody on the server that is not
     * modeled by the client. Its purpose is to respawn the player.
     *
     * @param id ID of the circus floor
     */
    CircusRespawn(int id, Server& serverRef);

    ~CircusRespawn() = default;

    /**
     * @brief custom collision response of circus floor
     *
     * @param ptr to the object class that this object collided with
     */
    void customCollision(ICustomPhysics* otherObject) override;

  private:
    Server& server;
};
