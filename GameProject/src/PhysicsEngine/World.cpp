/**
 * @file World.cpp
 * @brief Definition of the World class.
 *
 * This file contains the definitions of the World class, including how to
 * handle adding/removing objects in the environment and how objects behave
 * through time. Additionally, there are debugger functions.
 */

#include "World.hpp"

using namespace std;
using namespace glm;

/**
 * Constructor function for the World class, using the provided gravity macro.
 */
World::World() {
    objects;
}

/**
 * Add an object to the environment.
 * @param object pointer to the object to add.
 */
void World::addObject(RigidBody* object) {
    objects.push_back(object);
}

/**
 * Removes the specified object if it exists.
 * @param object pointer to the object to remove.
 */
void World::removeObject(RigidBody* object) {
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
    for (RigidBody* obj : objects) {
        // apply kinematics
        obj->applyGravity();
        obj->updateVelocity(dt);
        obj->updatePosition(dt);
    }
}

void World::resolveCollisions(float dt) {
    // vector<Collision> collisions;

    // for (RigidBody* a : m_objects)
    // for (RigidBody* b : m_objects) 
    // {
    //     if (a == b)
    //         break;

    //     if (!a->Collider || !b->Collider)
    //         continue;

    //     CollisionPoints points = TestCollision(
    //         a->Collider, a->Transform,
    //         b->Collider, b->Transform
    //     );

    //     if (points.HasCollision)
    //         collisions.emplace_back(a, b, points);
    // }

    // cout << "COLLISION" << endl;
}



/* TESTING */

World world;

Collider capsule{CAPSULE};
Transform transform1{
    vec3(0.0f, 25.0f, 0.0f),
    vec3(1.0f, 1.0f, 1.0f),
    quat(1.0f, 0.0f, 0.0f, 0.0f)
};
RigidBody object1{
    vec3(0.0f, 0.0f, 0.0f),
    vec3(0.0f, 0.0f, 0.0f),
    10.0f,
    &capsule,
    &transform1
};

// Transform transform2{
//     vec3(0, 25, 0),
//     vec3(1, 1, 1),
//     quat(1.0f, 0.0f, 0.0f, 0.0f)
// };
// RigidBody object2{
//     vec3(10, 25, 0),
//     vec3(0, 0, 0),
//     10.0f,
//     &capsule,
//     &transform2
// };

void keyCallback(
    GLFWwindow *window, int key, int scancode, int action, int mods);

/**
 * Main function to debug physics
 */
int main() {
    cout << "STARTING" << endl;

    world.addObject(&object1);
    // world.addObject(&object2);

    GLFWwindow *window;

    // initialize library
    if (!glfwInit()) {
        cout << "Failed to initialize library" << endl;
        return -1;
    }

    window = glfwCreateWindow(200, 200, "Test", nullptr, nullptr);

    glfwSetKeyCallback(window, keyCallback);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window) {
        cout << "Failed to open window" << endl;
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {

        glfwSwapBuffers(window);

        glfwPollEvents();

        world.step(0.05f);
        cout << object1.getPosition().x << " " << object1.getPosition().y << " " << object1.getPosition().z << " " << object1.getVelocity().y << endl;
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    glfwTerminate();
}

void keyCallback(
    GLFWwindow *window, int key, int scancode, int action, int mods) {

    vec3 position = object1.getPosition();
    vec3 velocity = object1.getVelocity();

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key)
        {
        case GLFW_KEY_W:
            object1.setVelocity(vec3(velocity.x, velocity.y, 10));
            break;
        
        case GLFW_KEY_A:
            object1.setVelocity(vec3(-10, velocity.y, velocity.z));
            break;

        case GLFW_KEY_S:
            object1.setVelocity(vec3(velocity.x, velocity.y, -10));
            break;

        case GLFW_KEY_D:
            object1.setVelocity(vec3(10, velocity.y, velocity.z));
            break;

        case GLFW_KEY_SPACE:
            if (object1.getPosition().y == 0) {
                object1.setVelocity(vec3(velocity.x, 10, velocity.z));
            }
            break;

        default:
            break;
        }
    } else {
        object1.setVelocity(vec3(0, velocity.y, 0));
    }
}