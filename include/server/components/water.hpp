#pragma once
#include "components/object.hpp"
#include "server.hpp"

class ICustomPhysics;

class Water : public ICustomPhysics {
  public:
    /**
     * @brief Constructs a water respawn plane with the given id.
     *
     * The water respawn plane is a rigidbody on the server that is not
     * modeled by the client. Its purpose is to respawn the player upon contact.
     *
     * @param id ID of the water
     * @param serverRef A reference to the server
     */
    Water(int id, Server& serverRef);

    ~Water() = default;

    /**
     * @brief Returns the rigid body of the object.
     *
     * @return RigidBody* reference to the object's rigid body.
     */
    RigidBody* getBody();

    /**
     * @brief Sets the rigid body of the object.
     *
     * @param newBody The new rigid body to set.
     */
    void setBody(RigidBody* newBody);

    /**
     * @brief Returns the ID of the lilypad.
     *
     * @return int ID of the lilypad.
     */
    int getID() const;

    /**
     * @brief custom collision response of lilypad
     *
     * @param ptr to the object class that this object collided with
     */
    void customCollision(ICustomPhysics* otherObject) override;

  private:
    int id;
    RigidBody* body = nullptr;
    Server& server;
};
