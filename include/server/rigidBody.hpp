/**
 * @file rigidBody.hpp
 * @brief Declaration of the RigidBody class.
 *
 * This file contains the declaration of the RigidBody class which outlines all
 * information necessary in calculating the kinematics of rigid bodies.
 */
#pragma once

#include <glm/glm.hpp>
#include "collider.hpp"
#include "transform.hpp"
using namespace glm;

#define ACCELERATION_GRAVITY -9.81f

class RigidBody {
public:
	/**
	 * @brief Constructs a RigidBody with specified physical properties and associated transform and collider.
	 *
	 * Initializes velocity, force, mass, transform, collider, static/dynamic status, and gravity.
	 * If the rigid body is static, gravity is disabled.
	 *
	 * @param velocity Initial velocity vector.
	 * @param force Initial force vector.
	 * @param mass Mass of the rigid body.
	 * @param transform Pointer to the associated Transform component.
	 * @param collider Pointer to the associated Collider component.
	 * @param isStatic Whether the rigid body is static (immovable).
	 * @param gravity Gravity vector applied to the body if dynamic.
	 */
	RigidBody(
		const vec3& velocity = vec3(0.0f),
		const vec3& force = vec3(0.0f),
		float mass = 0.0f,
		Transform* transform = nullptr,
		Collider* collider = nullptr,
		bool isStatic = false,
		const vec3& gravity = vec3(0, ACCELERATION_GRAVITY, 0));
	~RigidBody();

	/**
	 * @brief Updates the rigid body's velocity based on accumulated forces and gravity.
	 *
	 * Applies gravity and any accumulated forces, then updates velocity using basic Newtonian physics.
	 * Resets the net force afterward.
	 *
	 * @param dt Time step duration in seconds.
	 */
	void updateVelocity(float dt);

	/**
	 * @brief Updates the rigid body's position based on its current velocity.
	 *
	 * Applies simple linear motion using the velocity over the given time step.
	 *
	 * @param dt Time step duration in seconds.
	 */
	void updatePosition(float dt);

	/**
	 * @brief Returns the current velocity of the rigid body.
	 *
	 * @return Current velocity vector.
	 */
	const vec3 getVelocity() const;

	/**
	 * @brief Sets the rigid body's velocity to a new value.
	 *
	 * @param newVelocity The new velocity vector.
	 */
	void setVelocity(vec3 newVelocity);

	/**
	 * @brief Returns the current accumulated force on the rigid body.
	 *
	 * @return Current force vector.
	 */
	const vec3 getForce() const;

	/**
	 * @brief Sets the rigid body's accumulated force to a new value.
	 *
	 * @param newForce The new force vector.
	 */
	void setForce(vec3 newForce);

	/**
	 * @brief Returns the current position of the rigid body.
	 *
	 * @return Current position vector.
	 */
	const vec3 getPosition() const;

	/**
	 * @brief Sets the rigid body's position to a new value.
	 *
	 * @param newPosition The new position vector.
	 */
	void setPosition(vec3 newPosition);

	/**
	 * @brief Returns the current facing direction of the rigid body.
	 *
	 * @return Current direction vector.
	 */
	const vec3 getDirection() const;

	/**
	 * @brief Sets the rigid body's facing direction to a new value.
	 *
	 * @param newDirection The new direction vector.
	 */
	void setDirection(vec3 newDirection);

	/**
	 * @brief Returns a pointer to the rigid body's collider.
	 *
	 * @return Pointer to the Collider component.
	 */
	const Collider* getCollider() const;

	/**
	 * @brief Returns whether the rigid body is static (immovable).
	 *
	 * @return True if static, false if dynamic.
	 */
	const bool getStatic() const;

private:
	// dynamics
	vec3 velocity;
	vec3 force;
	vec3 gravity;
	float mass;

	// body
	Collider* collider;
	Transform* transform;
	bool isStatic;
};