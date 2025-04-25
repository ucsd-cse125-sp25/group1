#include "World.hpp"

using namespace std;
using namespace glm;

World::World() {}
World::~World() {}

void World::addObject(RigidBody* object) {
    objects.push_back(object);
}

void World::removeObject(RigidBody* object) {
    auto it = find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void World::step(float dt) {
    for (RigidBody* obj : objects) {
        // apply kinematics
        obj->updateVelocity(dt);
        obj->updatePosition(dt);
    }
}

void World::resolveCollisions() {
    for (RigidBody* a : objects)
        for (RigidBody* b : objects) {
            // iterate b up until a
            if (a == b)
                break;

            // skip iteration if either object isn't a collider or both objects are static
            if (!a->getCollider() || !b->getCollider() || (a->getStatic() && b->getStatic()))
                continue;

            Collision collision = testCollision(a, b);

            if (collision.isColliding) solveCollision(a, b, collision);
        }
}