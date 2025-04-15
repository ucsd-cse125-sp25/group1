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

bool Test_Box_Box(
	const RigidBody* boxA, const RigidBody* boxB);

bool Test_Sphere_Sphere(
	const RigidBody* sphereA, const RigidBody* sphereB);

bool Test_Box_Sphere(
	const RigidBody* box, const RigidBody* sphere);

bool TestCollision(const RigidBody* objA, const RigidBody* objB);

#endif