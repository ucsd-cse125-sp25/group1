#include "components/pianoKey.hpp"
#include <iostream>
#include "json.hpp"
#include "piano.hpp"
#include "server.hpp"

using json = nlohmann::json;

PianoKey::PianoKey(int id, float kConstant, float dampFactor, glm::vec3 target,
                   glm::vec3 initialPosition, Server& serverRef, Piano* pianoRef)
    : Object(id), kConstant(kConstant), dampFactor(dampFactor), target(target),
      initialPosition(initialPosition), server(serverRef), piano(pianoRef) {}

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
    std::cout << "pianokey collision" << std::endl;
    if (Player* player = dynamic_cast<Player*>(otherObject)) {
        updatePosition(config::TICK_RATE, true);

        // play sound
        // if(!player->getPianoSfxCooldown()) {
        json sfx;
        sfx["type"] = "sfx";
        sfx["sfx_id"] = config::PIANO_KEY_SFX[getID()];
        sfx["client_id"] = player->getID();
        sfx["action"] = "play";
        sfx["volume"] = config::PIANO_KEY_VOL;

        std::string sfxPacket = sfx.dump() + "\n";
        server.broadcastMessage(sfxPacket);

        std::cout << "Piano Key " << getID() << " pressed by player " << player->getID()
                  << std::endl;
        // player->setPianoSfxCooldown(true);
        //}
    } else {
        updatePosition(config::TICK_RATE, false);
    }
}
