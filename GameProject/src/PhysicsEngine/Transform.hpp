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

// describes a potential collision between two objects
struct CollisionPoints {
	vec3 a; 				// furthest point of A into B
	vec3 b; 				// furthest point of B into A
	vec3 normal; 			// B – A normalized
	float depth;    		// Length of B – A
	bool isColliding;
};
 
// describes an objects location
struct Transform {
	vec3 position;
	vec3 scale;
	quat rotation;
};

#endif