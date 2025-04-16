/**
 * @file World.hpp
 * @brief Declaration of the World class.
 *
 * This file contains the declaration of the World class which describes the
 * physics world, including all the objects within the environment, gravity,
 * and helper functions which help in controlling and managing the environment.
 */

#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <iostream>
#include <glm/glm.hpp>      // vec3
#include <algorithm>        // find
#include <GLFW/glfw3.h>     // keyCallback
#include <thread>           // sleep_for
#include <chrono>           // chrono
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Transform.hpp"
#include "CollisionDetection.hpp"
using namespace std;

class RigidBody;

class World {
    private:
        vector<RigidBody*> objects;
     
    public:
        World();
        void addObject(RigidBody* object);
        void removeObject(RigidBody* object);  
        void step(float dt);
        void resolveCollisions(float dt);
    };

#endif