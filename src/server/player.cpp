#include "player.hpp"

using namespace std;

Player::Player(const std::string& playerName, int roomID, vec3 position, vec3 direction)
    : 
    name(playerName),
    curRoomID(roomID), 
    body(
        vec3(0.0f),
        vec3(0.0f),
        config::PLAYER_WEIGHT,
        new Transform { position, direction },
        new BoxCollider{
            AABB,
            vec3(-config::PLAYER_WIDTH / 2, -config::PLAYER_HEIGHT / 2, -config::PLAYER_WIDTH / 2),
            vec3(config::PLAYER_WIDTH / 2, config::PLAYER_HEIGHT / 2, config::PLAYER_WIDTH / 2)
        }
    ) {}

Player::~Player() {}

string Player::getName() const {
    return name;
}

int Player::getCurRoomID() const {
    return curRoomID;
}

void Player::setCurRoomID(int roomID) {
    curRoomID = roomID;
}

RigidBody& Player::getBody() {
    return body;
}

void Player::handleInput(string action) {
    // variable for projection
    vec3 direction = body.getDirection();
    mat4 transform = mat4(1.0f);
    vec3 axis = vec3(0, 1, 0);
    float angle = glm::radians(90.0f);

    if (action == "move_forward") {
        direction = direction;
    } else if (action == "move_backward") {
        direction = -direction;
    } else if (action == "strafe_left") {
        // project onto 90 degree left rotation
        direction = vec3(rotate(transform, angle, axis) * vec4(direction, 0.0f));
    } else if (action == "strafe_right") {
        // project onto 90 degree right rotation
        direction = vec3(rotate(transform, -angle, axis) * vec4(direction, 0.0f));
    } else if (action == "jump" && abs(body.getVelocity().y) < 1e-6f) {
        // if grounded, jump
        body.setVelocity(vec3(body.getVelocity().x, config::PLAYER_SPEED*0.5, body.getVelocity().z));
    } else {
        return;
    }
    
    direction = normalize(vec3(direction.x, 0.0f, direction.z));
    body.setVelocity(body.getVelocity() + direction * config::PLAYER_SPEED);
}
