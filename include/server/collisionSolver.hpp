/**
 * @file collisionSolver.hpp
 * @brief Declaration of the collision solving functions.
 *
 * This file contains the declaration of the solveCollision which, given two rigid bodies, will
 * resolve any potential collision.
 */
#pragma once

#include "collider.hpp"
#include "collisionDetection.hpp"
#include "rigidBody.hpp"

/**
 * @brief Resolves collision between two rigid bodies by correcting positions and adjusting
 * velocities.
 *
 * If both rigid bodies are dynamic (moving), the collision depth is split evenly,
 * and each body's velocity is modified to slide along the contact surface by removing
 * the component into the collision normal.
 *
 * If one body is static (or nearly stationary), only the dynamic body's position is corrected,
 * and its velocity is projected onto the surface to allow sliding without penetration.
 *
 * @param a Pointer to the first rigid body involved in the collision.
 * @param b Pointer to the second rigid body involved in the collision.
 * @param collision Collision information containing the collision normal and penetration depth.
 */
void solveCollision(RigidBody* a, RigidBody* b, Collision collision);
