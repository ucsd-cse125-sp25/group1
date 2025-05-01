#pragma once
#include <glm/glm.hpp>
#include "rigidBody.hpp"

class Object
{
public:
    /**
     * @brief Constructs an object with a given id, room ID, position, and direction.
     *
     * Initializes an object at the specified position and orientation,
     * assigning it a box collider based on the given width and height.
     * An object is any item in a room that is not interactable via a key press.
     * It only has a rigidbody that can be collided with.
     *
     * @param id ID of the object
     * @param position Initial position of the player.
     * @param direction Initial facing direction of the player.
     * @param width width of the object.
     * @param height height of the object.
     */
    Object(int id, glm::vec3 position, glm::vec3 direction, float width, float height);

    ~Object() = default;
    
private:
    int id;
    RigidBody body;
};