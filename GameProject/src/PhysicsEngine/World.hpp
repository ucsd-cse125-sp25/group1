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
using namespace std;

#define ACCELERATION_GRAVITY -9.81f

class Object;

class World {
    private:
        vector<Object*> objects;
        glm::vec3 gravity;
     
    public:
        World();
        void addObject(Object* object);
        void removeObject(Object* object);  
        void step(float dt);
    };

#endif