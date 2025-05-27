#include "components/pianoKey.hpp"

PianoKey::PianoKey(int id, float kConstant, float dampFactor, glm::vec3 target,
                   glm::vec3 initialPosition)
    : Object(id), kConstant(kConstant), dampFactor(dampFactor), target(target),
      initialPosition(initialPosition) {}

void PianoKey::updatePosition(float dt, bool isPressed) {
    RigidBody* body = this->getBody();
    // check if pressed, return to initial position if not pressed
    vec3 setPoint = isPressed ? target : initialPosition;

    // F = -kConstant * x - dampFactor * v
    glm::vec3 acceleration =
        -kConstant * (body->getPosition() - setPoint) - dampFactor * body->getVelocity();
    // v = v0 + a * dt
    body->setVelocity(body->getVelocity() + acceleration * dt);
    // x = x0 + v * dt
    body->setPosition(body->getPosition() + body->getVelocity() * dt);
}

void PianoKey::customCollision(ICustomPhysics* otherObject) {
    // if colliding with a player, lower the key
    if (Player* player = dynamic_cast<Player*>(otherObject)) {
        updatePosition(config::TICK_RATE, true);
    } else {
        updatePosition(config::TICK_RATE, false);
    }
}
