/**
 * @file World.cpp
 * @brief Definition of the World class.
 *
 * This file contains the definitions of the World class, including how to
 * handle adding/removing objects in the environment and how objects behave
 * through time. Additionally, there are debugger functions.
 */

#include "World.hpp"
#include "Object.hpp"

using namespace std;

/**
 * Constructor function for the World class, using the provided gravity macro.
 */
World::World() {
    objects;
    gravity = glm::vec3(0, ACCELERATION_GRAVITY, 0);
}

/**
 * Add an object to the environment.
 * @param object pointer to the object to add.
 */
void World::addObject(Object* object) {
    objects.push_back(object);
}

/**
 * Removes the specified object if it exists.
 * @param object pointer to the object to remove.
 */
void World::removeObject(Object* object) {
    auto it = find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

/**
 * Apply all changes to all objects' kinematics during the current time step.
 * Apply gravity, update velocity/position, reset forces
 * @param dt change in time since last step
 */
void World::step(float dt) {
    for (Object* obj : objects) {
        // apply gravity, F = m*a
        if (obj->position.y > 0) {
            obj->force += obj->mass * gravity;

        // stop at floor
        } else {
            obj->position.y = 0.0f;
            obj->velocity.y = 0.0f;
        }

        // apply kinematics
        // v = v_0 + (F/m) * dt
        obj->velocity += obj->force / obj->mass * dt;
        // x = x_0 + v*dt
        obj->position += obj->velocity * dt;

        // reset net force at the end
        obj->force = glm::vec3(0, 0, 0);
    }
}

/**
 * Main function to debug physics
 */
int main() {
    World world;

    Object object{
        glm::vec3(0, 10000, 0),
        glm::vec3(0, 0, 0),
        glm::vec3(10, 0, 0),
        10.0f
    };
    
    world.addObject(&object);

    int time = 0;
    while (1) {
        time++;
        world.step(0.001f);
        cout << object.position.x << " " << object.position.y << " " << object.position.z << endl;
        int sign = signbit(object.velocity.x) ? -1 : 1;
        if (time % 100000 == 0) object.force.x = -10 * sign;
    }
}