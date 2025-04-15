/**
 * @file Transform.hpp
 * @brief Declaration of the Transform class.
 *
 * This file contains the declaration of the Transform class which specifies
 * the orientation of an object and collision detection geometry.
 */
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
using namespace glm;

// describes an objects location
struct Transform {
	vec3 position;
	vec3 direction;
};

#endif