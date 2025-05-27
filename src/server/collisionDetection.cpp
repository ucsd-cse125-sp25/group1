#include "collisionDetection.hpp"

using namespace std;
using namespace glm;

Collision testCollision(const RigidBody* boxA, const RigidBody* boxB) {

    // retrieve colliders
    const BoxCollider* colliderA = static_cast<const BoxCollider*>(boxA->getCollider());
    const BoxCollider* colliderB = static_cast<const BoxCollider*>(boxB->getCollider());

    // get min and max points of each AABB
    const vec3 minA = colliderA->minCorner + boxA->getPosition();
    const vec3 maxA = colliderA->maxCorner + boxA->getPosition();
    const vec3 minB = colliderB->minCorner + boxB->getPosition();
    const vec3 maxB = colliderB->maxCorner + boxB->getPosition();

    // check if there is overlap in 3D
    bool isColliding = (maxA.x > minB.x && minA.x < maxB.x) &&
                       (maxA.y > minB.y && minA.y < maxB.y) && (maxA.z > minB.z && minA.z < maxB.z);

    // get depth of overlap for each axis
    float overlapX = std::min(maxA.x, maxB.x) - std::max(minA.x, minB.x);
    float overlapY = std::min(maxA.y, maxB.y) - std::max(minA.y, minB.y);
    float overlapZ = std::min(maxA.z, maxB.z) - std::max(minA.z, minB.z);

    // assume x has least overlap
    float depth = overlapX;
    vec3 normal = (boxA->getPosition().x < boxB->getPosition().x ? vec3(-1, 0, 0) : vec3(1, 0, 0));

    // otherwise y has least overlap
    if (overlapY < depth) {
        depth = overlapY;
        normal = (boxA->getPosition().y < boxB->getPosition().y ? vec3(0, -1, 0) : vec3(0, 1, 0));
    }

    // otherwise z has least overlap
    if (overlapZ < depth) {
        depth = overlapZ;
        normal = (boxA->getPosition().z < boxB->getPosition().z ? vec3(0, 0, -1) : vec3(0, 0, 1));
    }

    Collision collision{
        normal,
        depth,
        isColliding,
    };

    return collision;
}
