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
	CAPSULE,
	PLANE
};

struct Collider {
	ColliderType type;
};

#endif