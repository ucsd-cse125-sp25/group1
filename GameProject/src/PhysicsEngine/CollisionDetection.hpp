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

struct Collision {
	RigidBody* ObjA;
	RigidBody* ObjB;
	CollisionPoints Points;
};

CollisionPoints Test_Capsule_Capsule(
	const Collider* a, const Transform* ta,
	const Collider* b, const Transform* tb);

CollisionPoints Test_Capsule_Plane(
	const Collider* a, const Transform* ta,
	const Collider* b, const Transform* tb);

using FindContactFunc = CollisionPoints(*)(
    const Collider*, const Transform*, 
    const Collider*, const Transform*);

CollisionPoints TestCollision(
	const Collider* a, const Transform* at, 
	const Collider* b, const Transform* bt)
{
	static const FindContactFunc tests[2][2] = 
	{
		// Capsule             Plane
		{ Test_Capsule_Capsule, Test_Capsule_Plane }, // Capsule
		{ nullptr,            nullptr           }  // Plane
	};

    // If we are passed a Plane vs Capsule, swap the 
	// colliders so it's a Capsule vs Plane
	bool swap = b->Type > a->Type;

	if (swap)
	{
		std::swap(a, b);
		std::swap(at, bt);
	}

    // now we can dispatch the correct function
	CollisionPoints points = tests[a->Type][b->Type](a, at, b, bt);

	// if we swapped the order of the colliders, to keep the
	// results consistent, we need to swap the points
	if (swap)
	{
		std::swap(points.A, points.B);
		points.Normal = -points.Normal;
	}

	return points;
}

#endif