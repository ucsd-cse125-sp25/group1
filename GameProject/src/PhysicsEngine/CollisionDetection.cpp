/**
 * @file CollisionDetection.hpp
 * @brief Declaration of the CollisionDetection class.
 *
 * This file contains the declaration of the CollisionDetection class which ...
 */

#include "CollisionDetection.hpp"

using namespace std;
using namespace glm;

bool Test_Box_Box(
	const RigidBody* boxA, const RigidBody* boxB) {

    const BoxCollider* colliderA =
        static_cast<const BoxCollider*>(boxA->getCollider());
    const BoxCollider* colliderB =
        static_cast<const BoxCollider*>(boxB->getCollider());
    const vec3 posA = boxA->getPosition();
    const vec3 posB = boxB->getPosition();
    return (
        colliderA->maxCorner.x + posA.x > colliderB->minCorner.x + posB.x &&
        colliderA->minCorner.x + posA.x < colliderB->maxCorner.x + posB.x &&
        colliderA->maxCorner.y + posA.y > colliderB->minCorner.y + posB.y &&
        colliderA->minCorner.y + posA.y < colliderB->maxCorner.y + posB.y &&
        colliderA->maxCorner.z + posA.z > colliderB->minCorner.z + posB.z &&
        colliderA->minCorner.z + posA.z < colliderB->maxCorner.z + posB.z
    );
}

bool Test_Sphere_Sphere(
	const RigidBody* sphereA, const RigidBody* sphereB) {

    const SphereCollider* colliderA =
        static_cast<const SphereCollider*>(sphereA->getCollider());
    const SphereCollider* colliderB =
        static_cast<const SphereCollider*>(sphereB->getCollider());
    return distance(colliderA->center, colliderB->center) < 
        (colliderA->radius + colliderB->radius);
}

bool Test_Box_Sphere(
	const RigidBody* box, const RigidBody* sphere) {

    const BoxCollider* colliderA =
        static_cast<const BoxCollider*>(box->getCollider());
    const SphereCollider* colliderB =
        static_cast<const SphereCollider*>(sphere->getCollider());

    vec3 pA = box->getPosition();
    vec3 minA = colliderA->minCorner + pA;
    vec3 maxA = colliderA->maxCorner + pA;

    vec3 closestPoint = clamp(colliderB->center, minA, maxA);

    return distance(closestPoint, colliderB->center) < colliderB->radius;
}

using collisionGrid = bool(*)(const RigidBody*, const RigidBody*);

bool TestCollision(const RigidBody* objA, const RigidBody* objB) {
	static const collisionGrid tests[2][2] = 
	{
		// Box             	Sphere
		{ Test_Box_Box, 	Test_Box_Sphere 	}, // Box
		{ nullptr,			Test_Sphere_Sphere	}  // Sphere
	};

	if (objA->getCollider()->type > objB->getCollider()->type) {
		swap(objA, objB);
	}

    collisionGrid testFunc =
        tests[objA->getCollider()->type][objB->getCollider()->type];

    if (!testFunc) {
        return false;
    }

    return testFunc(objA, objB);
}