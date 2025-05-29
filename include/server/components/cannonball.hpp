#pragma once

#include <glm/glm.hpp>
#include "config.hpp"
#include "object.hpp"
#include "player.hpp"

class Cannonball : public Object {
  public:
    Cannonball(int id, glm::vec3 cannonPosition);

    ~Cannonball() = default;

    /**
     * @brief Calculate direction of player and set velocity to shoot at them.
     *
     * @param player Player to shoot at
     */
    void fire(Player* player);

    /**
     * @brief On collision with player, kill player; on collision with static object,
     * "destroy"/reset cannonball.
     *
     * @param otherObject Object to check collision with
     */
    void customCollision(ICustomPhysics* otherObject) override;

  private:
    glm::vec3 cannonPosition;
};
