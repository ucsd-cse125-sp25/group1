/**
 * @file collisionDetection.hpp
 * @brief Declaration of the Collision type and collision detection.
 *
 * This file contains the declaration of the Collision type which outlines all
 * information needed in calculating collision response and collision detection.
 */
#pragma once

#include <algorithm>
#include "collider.hpp"
#include "rigidBody.hpp"
#include "transform.hpp"

class RigidBody;

struct Collision {
    vec3 normal;      // contact normal
    float depth;      // depth of penetration
    bool isColliding; // is there a collision
};

/**
 * @brief Performs collision detection between two axis-aligned bounding boxes.
 *
 * This function checks whether the AABBs associated with two RigidBody objects overlap
 * in 3D space. If a collision is detected, it calculates the collision normal and
 * penetration depth along the axis of least overlap. The normal points from boxA
 * into boxB. The result is returned in a Collision struct.
 *
 * @param boxA Pointer to the first RigidBody containing an AABB collider.
 * @param boxB Pointer to the second RigidBody containing an AABB collider.
 * @return Collision struct containing:
 *         - isColliding: true if the boxes overlap, false otherwise
 *         - normal: unit direction of the collision
 *         - depth: penetration depth along the collision normal
 *         - isSwapped: denotes if boxA and boxB was swapped in function call (false by default)
 */
Collision testCollision(const RigidBody* objA, const RigidBody* objB);
