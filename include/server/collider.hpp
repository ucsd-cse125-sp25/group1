/**
 * @file collider.hpp
 * @brief Declaration of the Collider type and helper types.
 *
 * This file contains the declaration of the Collider type which outlines all
 * the different collider types a rigid body can have.
 */
#pragma once

#include <glm/glm.hpp>

using namespace glm;

// types of colliders
enum ColliderType {
    AABB, // standard rigid body
    NONE  // ignores collision solver, custom collision valid still
};

// collider of type ColliderType
struct Collider {
    ColliderType type;
};

// AABB box collider geometry
struct BoxCollider : Collider {
    vec3 minCorner; // least x, y, z corner relative to center
    vec3 maxCorner; // greatest x, y, z corner relative to center
};
