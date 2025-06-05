#include "rigidBody.hpp"
#include <iostream>

RigidBody::RigidBody(const vec3& velocity, const vec3& force, float mass, Transform* transform,
                     Collider* collider, ICustomPhysics* customPhysics, World* world, bool isStatic,
                     const vec3& gravity)
    : velocity(velocity), force(force), mass(mass), transform(transform), collider(collider),
      customPhysics(customPhysics), world(world), isStatic(isStatic),
      gravity(isStatic ? glm::vec3(0.0f) : gravity) {

    BoxCollider* temp = static_cast<BoxCollider*>(collider);
    colliderOriginal = new BoxCollider{temp->type, temp->minCorner, temp->maxCorner};
}

RigidBody::~RigidBody() {
    world->removeObject(this);
    delete transform;
    delete collider;
}

void RigidBody::updateVelocity(float dt) {
    if (isStatic)
        return;

    // apply gravity, F = m*a
    force += mass * gravity;

    // v = v_0 + (F/m) * dt
    velocity += force / mass * dt;

    // reset net force at the end
    force = glm::vec3(0.0f, 0.0f, 0.0f);
}

void RigidBody::updatePosition(float dt) {
    if (isStatic)
        return;

    // x = x_0 + v*dt
    transform->position += velocity * dt;

    if (transform->position.y < -50) {
        // reset if too low
        transform->position = glm::vec3(0.0f, 5.0f, 0.0f);
        velocity.y = 0.0f; // reset vertical velocity
    }
}

const vec3 RigidBody::getVelocity() const {
    return velocity;
}

void RigidBody::setVelocity(vec3 newVelocity) {
    velocity = newVelocity;
}

const vec3 RigidBody::getForce() const {
    return force;
}

void RigidBody::setForce(vec3 newForce) {
    force = newForce;
}

const vec3 RigidBody::getPosition() const {
    return transform->position;
}

void RigidBody::setPosition(vec3 newPosition) {
    transform->position = newPosition;
}

const vec3 RigidBody::getDirection() const {
    return transform->direction;
}

void RigidBody::transformBox(mat3 rotation) {
    float a, b;
    float Amin[3], Amax[3];
    float Bmin[3] = {0}, Bmax[3] = {0};
    int i, j;

    BoxCollider* box = static_cast<BoxCollider*>(colliderOriginal);
    BoxCollider* boxNew = static_cast<BoxCollider*>(collider);

    // Copy box into a min array and a max array for easy reference
    Amin[0] = box->minCorner.x;
    Amax[0] = box->maxCorner.x;
    Amin[1] = box->minCorner.y;
    Amax[1] = box->maxCorner.y;
    Amin[2] = box->minCorner.z;
    Amax[2] = box->maxCorner.z;

    // Find the extreme points by considering the product of the min
    // and max with each component of the rotation matrix
    for (i = 0; i < 3; i++) {
        if (i == 1)
            continue; // skip pitch
        for (j = 0; j < 3; j++) {
            a = rotation[j][i] * Amin[j];
            b = rotation[j][i] * Amax[j];
            if (a < b) {
                Bmin[i] += a;
                Bmax[i] += b;
            } else {
                Bmin[i] += b;
                Bmax[i] += a;
            }
        }
    }
    Bmin[1] = Amin[1];
    Bmax[1] = Amax[1];

    // Copy the result into the new box
    boxNew->minCorner = vec3(Bmin[0], Bmin[1], Bmin[2]);
    boxNew->maxCorner = vec3(Bmax[0], Bmax[1], Bmax[2]);
}

void RigidBody::setDirection(vec3 newDirection) {
    // Calculate the transformation matrix for the rotation
    vec3 flattenedNew = vec3(newDirection.x, 0, newDirection.z);
    float radians = acos(dot(vec3(1.0f, 0.0f, 0.0f), normalize(flattenedNew)));
    mat3 rotation = mat3(rotate(mat4(1.0f), radians, glm::vec3(0, 1, 0)));

    // Resize the AABB based on the rotation
    if (transform->direction != newDirection)
        transformBox(rotation);

    // Update the facing direction of the rigid body
    transform->direction = newDirection;
}

const Collider* RigidBody::getCollider() const {
    return collider;
}

ICustomPhysics* RigidBody::getCustomPhysics() const {
    return customPhysics;
}

const bool RigidBody::getStatic() const {
    return isStatic;
}
