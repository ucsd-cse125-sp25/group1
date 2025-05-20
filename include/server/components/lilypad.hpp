#pragma once
#include <glm/glm.hpp>
#include "rigidBody.hpp"

class Server;

class LilyPad : public ICustomPhysics {
  public:
    /**
     * @brief Constructs a Lilypad with a given id, solidity, position, and direction.
     *
     * Initializes a lilypad at the specified position and orientation, with
     * the property of whether or not the player will fall through when jumping
     * on the lilypad.
     *
     * @param id ID of the object
     * @param isGood whether the lilypad will hold the player or fall through on impact
     * @param position position of the object.
     * @param direction facing direction of the object.
     */
    LilyPad(int id, bool isGood, Server& serverRef);

    ~LilyPad() = default;

    /**
     * @brief Returns the rigid body of the object.
     *
     * @return RigidBody& reference to the object's rigid body.
     */
    RigidBody* getBody();

    /**
     * @brief Sets the rigid body of the object.
     *
     * @param newBody The new rigid body to set.
     */
    void setBody(RigidBody* newBody);

    void customCollision(ICustomPhysics* otherObject) override;

    /**
     * @brief Returns the ID of the lilypad.
     *
     * @return int ID of the lilypad.
     */
    int getID() const;

    /**
     * @brief Returns whether the lilypad is good or bad.
     *
     * @return bool true if the lilypad is good, false if it is bad.
     */
    bool isGoodLilyPad() const;

  private:
    int lilyPadID;
    bool isGood;
    RigidBody* body = nullptr;
    Server& server;
};