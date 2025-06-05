#pragma once
#include "components/object.hpp"

class ICustomPhysics;
class Server;

class Splash : public Object {
  public:
    /**
     * @brief Constructs a splash plane for water splash sfx trigger with the given id
     *
     * The splash plane is a rigidbody on the server that is not
     * modeled by the client. Its purpose is to play the water splash sfx.
     *
     * @param id ID of the splash
     */
    Splash(int id, Server& serverRef);

    ~Splash() = default;

    /**
     * @brief custom collision response of splash
     *
     * @param ptr to the object class that this object collided with
     */
    void customCollision(ICustomPhysics* otherObject) override;

  private:
    Server& server;
};
