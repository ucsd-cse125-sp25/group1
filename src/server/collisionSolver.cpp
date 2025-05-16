#include "collisionSolver.hpp"
#include <iostream>
using namespace std;

/**
 * Calculates the component of a rigid body's velocity that is tangent to the surface
 * of a collision. This represents the motion parallel to the collision surface,
 * excluding any motion in the direction of the collision normal (i.e., normal impulse).
 *
 * @param body       Pointer to the RigidBody whose velocity is being analyzed.
 * @param collision  Pointer to the Collision object containing the collision normal.
 * @return           A vec3 representing the velocity vector tangential to the collision surface.
 */
vec3 calculateTangentVelocity(RigidBody* body, Collision* collision) {
    float velocityMagnitude = length(body->getVelocity());
    vec3 velocityNormal = body->getVelocity() / velocityMagnitude;
    vec3 undesiredMotion =
        collision->normal * dot(velocityNormal, collision->normal);
    vec3 desiredMotion = velocityNormal - undesiredMotion;
    return desiredMotion * velocityMagnitude;
}

void solveCollision(RigidBody* a, RigidBody* b, Collision collision) {
    // skip standard collision resolution if either collider is NONE, which ignores collision
    if (!(a->getCollider()->type == NONE || b->getCollider()->type == NONE)) {
        cout << a->getCollider()->type << endl;
        // check if both dynamic, split positioning correction
        if (length(a->getVelocity()) >= 1e-6f && length(b->getVelocity()) >= 1e-6f) {
            // push object a out of b
            vec3 newPositionA =
                a->getPosition() + collision.normal * collision.depth * 0.5f;
            a->setPosition(newPositionA);

            // push object b out of a
            vec3 newPositionB =
                b->getPosition() - collision.normal * collision.depth * 0.5f;
            b->setPosition(newPositionB);

            // modify objects' velocities to slide on contact surface
            a->setVelocity(calculateTangentVelocity(a, &collision));
            b->setVelocity(calculateTangentVelocity(b, &collision));

            // otherwise, one is static so correct position of dynamic
        }
        else {
            // check which one is static, and correct position/velocity for dynmaic
            if (length(a->getVelocity()) < 1e-6f) {
                a->setVelocity(vec3(0.0f));
                collision.normal = -collision.normal;
                swap(a, b);
            }

            // push dynamic object out of static
            vec3 newPosition =
                a->getPosition() + collision.normal * collision.depth;
            a->setPosition(newPosition);

            // modify dynamic object velocity to slide on contact surface
            float velocityMagnitude = length(a->getVelocity());
            if (velocityMagnitude < 1e-6f) {
                a->setVelocity(vec3(0.0f));
                return;
            }
            a->setVelocity(calculateTangentVelocity(a, &collision));
        }
    }
    ICustomPhysics* aCustomPhysics = a->getCustomPhysics();
    ICustomPhysics* bCustomPhysics = b->getCustomPhysics();
    if (aCustomPhysics != nullptr) aCustomPhysics->customCollision(bCustomPhysics);
    if (bCustomPhysics != nullptr) bCustomPhysics->customCollision(aCustomPhysics);
}
