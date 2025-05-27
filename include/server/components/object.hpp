#pragma once
#include <glm/glm.hpp>
#include "rigidBody.hpp"

class Object : public ICustomPhysics {
  public:
    /**
     * @brief Constructs an object with a given id.
     *
     * Initializes an object with a given id.
     *
     * @param id ID of the object
     */
    Object(int id);

    ~Object() = default;

    /**
     * @brief Returns the ID of the object.
     *
     * @return int ID of the object.
     */
    int getID() const;

    /**
     * @brief Returns the rigid body of the object.
     *
     * @return RigidBody& reference to the object's rigid body.
     */
    RigidBody* getBody();

    /**
     * @brief Sets rigid body of object to argument.
     */
    void setBody(RigidBody* newBody);

    void customCollision(ICustomPhysics* otherObject) override;

  private:
    int objectID;
    RigidBody* body = nullptr;
};
