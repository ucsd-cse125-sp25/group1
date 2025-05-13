#pragma once
#include <glm/glm.hpp>
#include "rigidBody.hpp"

class LilyPad : public ICustomPhysics
{
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
    LilyPad(int id, bool isGood, const glm::vec3& position, const glm::vec3& direction);

    ~LilyPad() = default;

    /**
    * @brief Returns the rigid body of the object.
    *
    * @return RigidBody& reference to the object's rigid body.
    */
    RigidBody& getBody();

    void customCollision(ICustomPhysics* otherObject) override;
    
private:
    int lilyPadID;
    bool isGood;
    RigidBody body;
};