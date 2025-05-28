#include "components/cannonball.hpp"

Cannonball::Cannonball(int id, glm::vec3 cannonPosition)
    : Object(id), cannonPosition(cannonPosition) {}

void Cannonball::fire(Player* player) {
    glm::vec3 fireDirection = glm::normalize(cannonPosition - player->getBody().getPosition());
    this->getBody()->setVelocity(fireDirection * config::CANNONBALL_SPEED);
}

void Cannonball::customCollision(ICustomPhysics* otherObject) {
    Object* object = dynamic_cast<Object*>(otherObject);
    Player* player = dynamic_cast<Player*>(otherObject);
    if (player) {
        // if colliding with a player, kill the player
        RigidBody& playerBody = player->getBody();
        // Make sure the player has no residual movement on respawn
        playerBody.setForce(glm::vec3{0.0f, 0.0f, 0.0f});
        playerBody.setVelocity(glm::vec3{0.0f, 0.0f, 0.0f});
        // TODO: add offset for the individual player, so 2 players don't spawn into the same spot.
        // TODO: update circus respawn in config with non-placeholder value
        playerBody.setPosition(config::CIRCUS_RESPAWN);
    } else if (object && object->getBody()->getStatic()) {
        // if colliding with a static object, reset the cannonball
        this->getBody()->setVelocity(glm::vec3(0, 0, 0));
        this->getBody()->setPosition(cannonPosition);
    }
}
