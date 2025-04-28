/**
 * @file transform.hpp
 * @brief Declaration of the Transform type.
 *
 * This file contains the declaration of the Transform type which specifies
 * the orientation of an object.
 */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
using namespace glm;

// describes an objects location
struct Transform {
	vec3 position;
	vec3 direction;
};