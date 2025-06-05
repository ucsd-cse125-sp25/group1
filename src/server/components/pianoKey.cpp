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
    if (Player* player = dynamic_cast<Player*>(otherObject)) {

        int pianoKeyID = getID();
        // play sound
        if (player->getPianoNote() != pianoKeyID) {
            json sfx;
            sfx["type"] = "sfx";
            sfx["sfx_id"] = config::PIANO_KEY_SFX[pianoKeyID];
            sfx["client_id"] = player->getID();
            sfx["action"] = "play";
            sfx["volume"] = config::PIANO_KEY_VOL;

            std::string sfxPacket = sfx.dump() + "\n";
            server.broadcastMessage(sfxPacket);


            int index = piano->getPlayedIndex();

            std::cout << "played index " << index << std::endl;
            if (pianoKeyID == piano->getSolutionNote(index)) {
                if (index < 14) {
                    piano->setPlayedIndex(index + 1);
                }
                // TODO : Send a good note message

            } else {
                piano->setPlayedIndex(0);

                // TODO : Send a bad note message reset the sheet music

                // Kill all players in the room
                server.PianoKill(config::PIANO_RESPAWN + config::PIANO_ROOM_POSITION);
            }
        }
    }
}
