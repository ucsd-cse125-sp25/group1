#include "cannonball.hpp"

Cannonball::Cannonball(int id, glm::vec3 cannonPosition) : Object(id), cannonPosition(cannonPosition) {}

Cannonball::~Cannonball() {}

void Cannonball::fire(Player* player) {
    glm::vec3 fireDirection = glm::normalize(cannonPosition - player->getBody()->getPosition());
    this->getBody()->setVelocity(fireDirection * config::CANNONBALL_SPEED);
}

void Cannonball::customCollision(ICustomPhysics* otherObject) {
    // if colliding with a player, kill the player
    if (Player* player = dynamic_cast<Player*>(otherObject)) {
        // TODO: kill the player

    // if colliding with a static object, reset the cannonball
    } else if (otherObject->getBody()->getStatic()) {
        this->getBody()->setVelocity(glm::vec3(0, 0, 0));
        this->getBody()->setPosition(cannonPosition);
    }
}
