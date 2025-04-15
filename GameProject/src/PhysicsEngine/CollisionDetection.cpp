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

    BoxCollider* colliderA = static_cast<BoxCollider*>(boxA->getCollider());
    BoxCollider* colliderB = static_cast<BoxCollider*>(boxB->getCollider());
    return (
        colliderA->maxCorner.x > colliderB->minCorner.x &&
        colliderA->minCorner.x < colliderB->maxCorner.x &&
        colliderA->maxCorner.y > colliderB->minCorner.y &&
        colliderA->minCorner.y < colliderB->maxCorner.y &&
        colliderA->maxCorner.z > colliderB->minCorner.z &&
        colliderA->minCorner.z < colliderB->maxCorner.z
    );
}

bool Test_Sphere_Sphere(
	const RigidBody* sphereA, const RigidBody* sphereB) {

    SphereCollider* colliderA =
        static_cast<SphereCollider*>(sphereA->getCollider());
    SphereCollider* colliderB =
        static_cast<SphereCollider*>(sphereB->getCollider());
    return distance(colliderA->center, colliderB->center) < 
        (colliderA->radius + colliderB->radius);
}

float clampToAABB(float point, BoxCollider* aabb, int axis) {
    if (point[axis] > aabb.maxCorner[axis])
        return aabb.maxCorner[axis];
    else if (point[axis] < aabb.minCorner[axis])
        return aabb.minCorner[axis];
    else
        return point[axis];
}

bool Test_Box_Sphere(
	const RigidBody* box, const RigidBody* sphere) {

    BoxCollider* colliderA =
        static_cast<BoxCollider*>(box->getCollider());
    SphereCollider* colliderB =
        static_cast<SphereCollider*>(sphere->getCollider());

    vec3 closestPoint = vec3(
        clampToAABB(colliderB->center, colliderA, 0),
        clampToAABB(colliderB->center, colliderA, 1),
        clampToAABB(colliderB->center, colliderA, 2),
    );

    float distance = distance(closestPoint, colliderB->center);

    return distance < colliderB->radius;
}

using collisionGrid = bool(*)(const RigidBody*, const RigidBody*);

bool TestCollision(const RigidBody* objA, const RigidBody* objB)
{
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
		tests[objA->getCollider()->type][objB->getCollider()->type](objA, objB);

	if (testFunc != nullptr) {
        return testFunc(objA, objB);
    }
    
    return false;
}