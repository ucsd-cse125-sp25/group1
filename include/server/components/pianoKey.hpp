#pragma once

#include <glm/glm.hpp>
#include "config.hpp"
#include "player.hpp"
#include "rigidBody.hpp"

class Server;
class Piano;

class PianoKey : public Object {
  public:
    PianoKey(int id, float kConstant, float dampFactor, glm::vec3 target, glm::vec3 initialPosition,
             Server& serverRef, Piano* pianoRef);

    ~PianoKey() = default;

    /**
     * @brief Updates the rigid body's position based on its current velocity according to spring
     * dynamics.
     *
     * Handles the spring dynamics of the piano key, including its velocity and position.
     *
     * @param dt Time step duration in seconds.
     */
    void updatePosition(float dt, bool isPressed);

    /**
     * @brief When player collides with piano key, simulate spring mechanics and play sound.
     *
     * @param otherObject Object to check collision with
     */
    void customCollision(ICustomPhysics* otherObject) override;

  private:
    float kConstant;
    float dampFactor;
    glm::vec3 target;
    glm::vec3 initialPosition;
    Server& server;
    Piano* piano;
};
