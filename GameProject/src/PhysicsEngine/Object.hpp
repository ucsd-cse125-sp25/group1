/**
 * @file Object.hpp
 * @brief Declaration of the Object class.
 *
 * This file contains the declaration of the Object class which outlines all
 * information necessary in calculating the kinematics of rigid bodies.
 */
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
using namespace glm;

struct Object {
	vec3 position;
    // note: player movement inputs directly change velocity, and players \
        are unaffected by friction
	vec3 velocity;
	vec3 force;
	float mass;
};

#endif