/**
 * @file RigidBody.hpp
 * @brief Declaration of the RigidBody class.
 *
 * This file contains the declaration of the RigidBody class which outlines all
 * information necessary in calculating the kinematics of rigid bodies.
 */
#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include <glm/glm.hpp>
#include "Collider.hpp"
#include "Transform.hpp"
using namespace glm;

#define ACCELERATION_GRAVITY -9.81f

class RigidBody {
	private:
		// note: player movement inputs directly change velocity, and players \
			are unaffected by friction
		vec3 velocity;
		vec3 force;
		vec3 gravity;
		float mass;
	
		Collider* collider;
		Transform* transform;

	public:
		RigidBody(
			const vec3& velocity = vec3(0.0f, 0.0f, 0.0f),
			const vec3& force = vec3(0.0f, 0.0f, 0.0f),
			float mass = 0.0f,
			Collider* collider = nullptr, Transform* transform = nullptr,
			const vec3& gravity = vec3(0, ACCELERATION_GRAVITY, 0)
			) :
				velocity(velocity),
				force(force),
				mass(mass),
				collider(collider),
				transform(transform),
				gravity(gravity)
			{

			}

		void applyGravity() {
			// apply gravity, F = m*a
			if (transform->position.y > 0) {
				force += mass * gravity;

			// stop at floor
			} else {
				transform->position.y = 0.0f;
				velocity.y = velocity.y < 0 ? 0.0f : velocity.y;
			}
		}

		void updateVelocity(float dt) {
			// v = v_0 + (F/m) * dt
			velocity += force / mass * dt;

			// reset net force at the end
			force = glm::vec3(0.0f, 0.0f, 0.0f);;
		}

		void updatePosition(float dt) {
			// x = x_0 + v*dt
			transform->position += velocity * dt;
		}

		vec3 getPosition() {
			return transform->position;
		}

		void setPosition(vec3 newPosition) {
			transform->position = newPosition;
		}

		vec3 getVelocity() {
			return velocity;
		}

		void setVelocity(vec3 newVelocity) {
			velocity = newVelocity;
		}

		ColliderType getCollider() {
			return collider;
		}
};

#endif