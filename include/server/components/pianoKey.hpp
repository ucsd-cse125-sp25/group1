#pragma once

class PianoKey : public Object {
  public:
    PianoKey(int id);

    ~PianoKey() = default;

    /**
     * @brief Updates the rigid body's position based on its current velocity according to spring
     * dynamics.
     *
     * Handles the spring dynamics of the piano key, including its velocity and position.
     *
     * @param dt Time step duration in seconds.
     */
    void updatePosition(float dt);

    /**
     * @brief When player collides with piano key, simulate spring mechanics and play sound.
     *
     * @param otherObject Object to check collision with
     */
    void customCollision(ICustomPhysics* otherObject) override;
};
