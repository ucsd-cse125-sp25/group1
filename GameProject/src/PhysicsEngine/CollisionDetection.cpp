/**
 * @file CollisionDetection.hpp
 * @brief Declaration of the CollisionDetection class.
 *
 * This file contains the declaration of the CollisionDetection class which ...
 */

#include "CollisionDetection.hpp"

using namespace std;
using namespace glm;

Collision Test_Box_Box(
	const RigidBody* boxA, const RigidBody* boxB) {

    const BoxCollider* colliderA =
        static_cast<const BoxCollider*>(boxA->getCollider());
    const BoxCollider* colliderB =
        static_cast<const BoxCollider*>(boxB->getCollider());
    const vec3 minA = colliderA->minCorner + boxA->getPosition();
    const vec3 maxA = colliderA->maxCorner + boxA->getPosition();
    const vec3 minB = colliderB->minCorner + boxB->getPosition();
    const vec3 maxB = colliderB->maxCorner + boxB->getPosition();

    bool isColliding = 
        (maxA.x > minB.x && minA.x < maxB.x) &&
        (maxA.y > minB.y && minA.y < maxB.y) &&
        (maxA.z > minB.z && minA.z < maxB.z);
    
    float overlapX = std::min(maxA.x, maxB.x) - std::max(minA.x, minB.x);
    float overlapY = std::min(maxA.y, maxB.y) - std::max(minA.y, minB.y);
    float overlapZ = std::min(maxA.z, maxB.z) - std::max(minA.z, minB.z);

    // assume x has least overlap
    float depth = overlapX;
    vec3 normal = (boxA->getPosition().x < boxB->getPosition().x ?
        vec3(-1, 0, 0) : vec3(1, 0, 0));

    // otherwise y has least overlap
    if (overlapY < depth) {
        depth = overlapY;
        normal = (boxA->getPosition().y < boxB->getPosition().y ?
            vec3(0, -1, 0) : vec3(0, 1, 0));
    }

    // otherwise z has least overlap
    if (overlapZ < depth) {
        depth = overlapZ;
        normal = (boxA->getPosition().z < boxB->getPosition().z ?
            vec3(0, 0, -1) : vec3(0, 0, 1));
    }

    Collision collision{
        normal,
        depth,
        isColliding,
        false
    };

    return collision;
}

Collision Test_Sphere_Sphere(
	const RigidBody* sphereA, const RigidBody* sphereB) {

    const SphereCollider* colliderA =
        static_cast<const SphereCollider*>(sphereA->getCollider());
    const SphereCollider* colliderB =
        static_cast<const SphereCollider*>(sphereB->getCollider());
    

    Collision collision{
        vec3(0, 0, 0),
        0,
        false,
        false
    };
    return collision;
    // return distance(colliderA->center, colliderB->center) < 
    //     (colliderA->radius + colliderB->radius);
}

Collision Test_Box_Sphere(
	const RigidBody* box, const RigidBody* sphere) {

    const BoxCollider* colliderA =
        static_cast<const BoxCollider*>(box->getCollider());
    const SphereCollider* colliderB =
        static_cast<const SphereCollider*>(sphere->getCollider());

    vec3 pA = box->getPosition();
    vec3 minA = colliderA->minCorner + pA;
    vec3 maxA = colliderA->maxCorner + pA;

    vec3 closestPoint = clamp(colliderB->center, minA, maxA);
    
    Collision collision{
        vec3(0, 0, 0),
        0,
        false,
        false
    };
    return collision;
    // return distance(closestPoint, colliderB->center) < colliderB->radius;
}

using collisionGrid = Collision(*)(const RigidBody*, const RigidBody*);

Collision TestCollision(const RigidBody* objA, const RigidBody* objB) {
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

    Collision collision{
        vec3(0, 0, 0),
        0,
        false,
        false
    };
    if (!testFunc) {
        return collision;
    }

    collision = testFunc(objA, objB);
    collision.isSwapped = objA->getCollider()->type > objB->getCollider()->type;

    return collision;
}