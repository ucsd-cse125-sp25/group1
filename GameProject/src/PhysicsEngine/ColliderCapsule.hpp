/**
 * @file ColliderCapsule.hpp
 * @brief Declaration of the ColliderCapsule class.
 *
 * This file contains the declaration of the ColliderCapsule class which ...
 */
#ifndef COLLIDER_CAPSULE_HPP
#define COLLIDER_CAPSULE_HPP

#include <glm/glm.hpp>
#include "Collider.h"

struct CapsuleCollider : Collider {
	vec3 pointBot;		// coordinate of the bottom hemispherical cap
	vec3 pointTop;		// coordinate of the top hemispherical cap
	float radius;		// radius of both cylinder and hemispheres
};

#endif