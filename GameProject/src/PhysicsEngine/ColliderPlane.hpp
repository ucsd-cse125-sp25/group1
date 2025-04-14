/**
 * @file ColliderPlane.hpp
 * @brief Declaration of the ColliderPlane class.
 *
 * This file contains the declaration of the ColliderPlane class which ...
 */
#ifndef COLLIDER_PLANE_HPP
#define COLLIDER_PLANE_HPP

#include <glm/glm.hpp>
#include "Collider.h"

struct PlaneCollider : Collider {
	vec3 normal;		// plane normal
	float distance;		// distance from origin
};

#endif