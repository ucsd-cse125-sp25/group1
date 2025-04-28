#include "rigidBody.hpp"

RigidBody::RigidBody(
	const vec3& velocity,
	const vec3& force,
	float mass,
	Transform* transform,
	Collider* collider,
	bool isStatic,
	const vec3& gravity
) :
	velocity(velocity),
	force(force),
	mass(mass),
	transform(transform),
	collider(collider),
	isStatic(isStatic),
	gravity(isStatic ? glm::vec3(0.0f) : gravity)
{}

RigidBody::~RigidBody() {
	delete transform;
	delete collider;
}

void RigidBody::updateVelocity(float dt) {
	if (isStatic) return;

	// apply gravity, F = m*a
	force += mass * gravity;

	// v = v_0 + (F/m) * dt
	velocity += force / mass * dt;

	// reset net force at the end
	force = glm::vec3(0.0f, 0.0f, 0.0f);
}

void RigidBody::updatePosition(float dt) {
	if (isStatic) return;

	// x = x_0 + v*dt
	transform->position += velocity * dt;
}

const vec3 RigidBody::getVelocity() const {
	return velocity;
}

void RigidBody::setVelocity(vec3 newVelocity) {
	velocity = newVelocity;
}

const vec3 RigidBody::getForce() const {
	return force;
}

void RigidBody::setForce(vec3 newForce) {
	force = newForce;
}

const vec3 RigidBody::getPosition() const {
	return transform->position;
}

void RigidBody::setPosition(vec3 newPosition) {
	transform->position = newPosition;
}

const vec3 RigidBody::getDirection() const {
	return transform->direction;
}

void RigidBody::setDirection(vec3 newDirection) {
	transform->direction = newDirection;
}

const Collider* RigidBody::getCollider() const {
	return collider;
}

const bool RigidBody::getStatic() const {
	return isStatic;
}