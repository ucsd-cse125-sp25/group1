/**
 * @file world.hpp
 * @brief Declaration of the World class.
 *
 * This file contains the declaration of the World class which describes the
 * physics world, including all the objects within the environment, gravity,
 * and helper functions which help in controlling and managing the environment.
 */

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <algorithm>        // find
#include "rigidBody.hpp"
#include "collider.hpp"
#include "transform.hpp"
#include "collisionDetection.hpp"
#include "collisionSolver.hpp"

using namespace std;

class World {
public:
    // constructor/destructor
    World();
    ~World();

    /**
     * @brief Adds a rigid body to the physics world.
     *
     * The object will be included in future physics updates and collision resolution steps.
     *
     * @param object Pointer to the RigidBody to add.
     */
    void addObject(RigidBody* object);

    /**
     * @brief Removes a rigid body from the physics world.
     *
     * Searches for the object in the list of active rigid bodies and removes it if found.
     *
     * @param object Pointer to the RigidBody to remove.
     */
    void removeObject(RigidBody* object);

    /**
     * @brief Advances the simulation by a time step.
     *
     * Updates the velocity and position of all rigid bodies based on applied forces and kinematics.
     *
     * @param dt Time step to advance the simulation by, in seconds.
     */
    void step(float dt);

    /**
     * @brief Detects and resolves collisions between rigid bodies.
     *
     * Iterates over all unique rigid body pairs and tests for collisions.
     * If a collision is detected, adjusts positions and velocities to resolve interpenetrations.
     *
     * Static objects are not moved or adjusted.
     */
    void resolveCollisions();
    
private:
    vector<RigidBody*> objects;
};