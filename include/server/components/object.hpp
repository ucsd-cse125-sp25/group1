#pragma once
#include <glm/glm.hpp>
#include "rigidBody.hpp"
#include <functional>

class Object : public ICustomPhysics {
  public:
    using CollisionCallback = std::function<void(ICustomPhysics*)>;

    /**
     * @brief Constructs an object with a given id.
     *
     * Initializes an object with a given id.
     *
     * @param id ID of the object
     */
    Object(int id);

    /**
     * @brief Constructs an object with a given id and collision callback.
     *
     * Initializes an object with a given id and a callback function that is called when a collision occurs.
     *
     * @param id ID of the object
     * @param func Callback function to be called on collision
     */
    Object(int id, CollisionCallback func);

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

  protected:
    int objectID;
    RigidBody* body = nullptr;
    CollisionCallback func;
};
