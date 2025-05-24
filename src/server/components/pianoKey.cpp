#include "pianoKey.hpp"

PianoKey::PianoKey(int id) : Object(id) {}

PianoKey::~PianoKey() {}

void PianoKey::customCollision(ICustomPhysics* otherObject) {
    // if colliding with a player, kill the player
    if (Player* player = dynamic_cast<Player*>(otherObject)) {
        a = -k * (pos - target) - d * vel
        vel += a * dt
        pos += vel * dt
        rigidBody.setPosition(pos)
    }
}
