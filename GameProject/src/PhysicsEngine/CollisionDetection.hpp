/**
 * @file CollisionDetection.hpp
 * @brief Declaration of the CollisionDetection class.
 *
 * This file contains the declaration of the CollisionDetection class which ...
 */
#ifndef COLLISION_DETECT_HPP
#define COLLISION_DETECT_HPP

#include "RigidBody.hpp"
#include "Transform.hpp"
#include "Collider.hpp"
#include <algorithm>

struct Collision {
	vec3 normal; 		// contact normal
	float depth;    	// depth of penetration
	bool isColliding;	// is there a collision
	bool isSwapped;		// did the points swap
};

Collision Test_Box_Box(
	const RigidBody* boxA, const RigidBody* boxB);

Collision Test_Sphere_Sphere(
	const RigidBody* sphereA, const RigidBody* sphereB);

Collision Test_Box_Sphere(
	const RigidBody* box, const RigidBody* sphere);

Collision TestCollision(const RigidBody* objA, const RigidBody* objB);

#endif