#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include "components/door.hpp"
#include "components/frog.hpp"
#include "components/lilypad.hpp"
#include "components/object.hpp"
#include "components/room.hpp"
#include "components/water.hpp"
#include "rigidBody.hpp"
#include "swamp.hpp"

class Swamp;

struct TransformData {
    glm::vec3 roomPosition;
    glm::vec3 position;
    glm::vec3 relativePosition;
    glm::vec3 relativeMinCorner;
    glm::vec3 relativeMaxCorner;
};

/**
 * @brief Initializes a generic Object with a unique ID and creates a default RigidBody for it.
 *
 * The Object is added to the provided object map using its ID as the key.
 * A RigidBody is constructed using the combined transform data and attached to the Object.
 *
 * @param data Transformation data including position and collider dimensions.
 * @param objects Pointer to the server's map storing Object instances.
 * @return Pointer to the initialized RigidBody.
 */
RigidBody* initObject(TransformData data, std::unordered_map<int, Object*>* objects);

/**
 * @brief Initializes a Door with room and key IDs, and assigns it a default RigidBody.
 *
 * The Door is inserted into the provided map with its ID as the key.
 * A RigidBody is created using the given transform data and attached to the Door.
 *
 * @param data Transformation and collider data for the door.
 * @param doors Pointer to the server's map storing Door instances.
 * @return Pointer to the initialized RigidBody.
 */
RigidBody* initDoor(TransformData data, std::unordered_map<int, Door*>* doors);

/**
 * @brief Initializes a Frog object with a unique ID and default RigidBody.
 *
 * The Frog is stored in the given object map with its ID.
 * A RigidBody is constructed using the transform data and assigned to the Frog.
 *
 * @param data Transform and collider bounds.
 * @param objects Pointer to the server's object map.
 * @param swamp Pointer to the Swamp environment managing the Frog.
 * @return Pointer to the initialized RigidBody.
 */
RigidBody* initFrog(TransformData data, std::unordered_map<int, Object*>* objects, Swamp* swamp);

/**
 * @brief Initializes a lily pad entity via the Swamp object and assigns it a RigidBody.
 *
 * The collider type is returned from `Swamp::createLilyPad`, along with the lily pad pointer.
 * A RigidBody is initialized with provided transform data and linked to the lily pad.
 *
 * @param data Transform data for positioning and bounding the lily pad.
 * @param swamp Pointer to the owning Swamp environment.
 * @return Pointer to the initialized RigidBody.
 */
RigidBody* initLilyPad(TransformData data, Swamp* swamp);

/**
 * @brief Initializes a water respawn plane from the Swamp and attaches a RigidBody.
 *
 * A Water object is created through the Swamp, and a non-collidable RigidBody is created with it.
 *
 * @param data Transform and bounds data for the water area.
 * @param swamp Pointer to the Swamp environment managing the water entities.
 * @return Pointer to the initialized RigidBody.
 */
RigidBody* initWater(TransformData data, Swamp* swamp);
