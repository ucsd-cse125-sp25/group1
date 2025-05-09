#include "collisionSolver.hpp"

using namespace std;

void solveCollision(RigidBody* a, RigidBody* b, Collision collision) {
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
    
        // modify object a velocity to slide on contact surface
        float velocityMagnitudeA = length(a->getVelocity());
        vec3 velocityNormalA = a->getVelocity() / velocityMagnitudeA;
        vec3 undesiredMotionA =
            collision.normal * dot(velocityNormalA, collision.normal);
        vec3 desiredMotionA = velocityNormalA - undesiredMotionA;
        vec3 newVelocityA = desiredMotionA * velocityMagnitudeA;
        a->setVelocity(newVelocityA);
    
        // modify object b velocity to slide on contact surface
        float velocityMagnitudeB = length(b->getVelocity());
        vec3 velocityNormalB = b->getVelocity() / velocityMagnitudeB;
        vec3 undesiredMotionB =
            collision.normal * dot(velocityNormalB, collision.normal);
        vec3 desiredMotionB = velocityNormalB - undesiredMotionB;
        vec3 newVelocityB = desiredMotionB * velocityMagnitudeB;
        b->setVelocity(newVelocityB);

    // otherwise, one is static so correct position of dynamic
    } else {
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
        vec3 velocityNormal = a->getVelocity() / velocityMagnitude;
        vec3 undesiredMotion =
            collision.normal * dot(velocityNormal, collision.normal);
        vec3 desiredMotion = velocityNormal - undesiredMotion;
        vec3 newVelocity = desiredMotion * velocityMagnitude;
        a->setVelocity(newVelocity);
    }
    
    if (a->getCustomPhysics() != nullptr) a->getCustomPhysics()->customCollision();
    if (b->getCustomPhysics() != nullptr) b->getCustomPhysics()->customCollision();
}
