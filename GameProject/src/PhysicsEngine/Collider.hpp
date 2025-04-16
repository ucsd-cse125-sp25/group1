/**
 * @file Collider.hpp
 * @brief Declaration of the Collider class.
 *
 * This file contains the declaration of the Collider class which outlines all
 * the different collider types a rigid body can have.
 */
#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/glm.hpp>
using namespace glm;

enum ColliderType {
	BOX,
	SPHERE
};

struct Collider {
	ColliderType type;
};

struct BoxCollider : Collider {
	vec3 minCorner;		// least x, y, z corner relative to center
	vec3 maxCorner;		// greatest x, y, z corner relative to center
};

struct SphereCollider : Collider {
	vec3 center;
	float radius;
};

#endif