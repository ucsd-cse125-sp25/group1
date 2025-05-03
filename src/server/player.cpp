#include "server/player.hpp"

Player::Player(int playerID, int roomID, glm::vec3 position, glm::vec3 direction)
    : 
    id(playerID),
    curRoomID(roomID), 
    body(
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        config::PLAYER_WEIGHT,
        new Transform { position, direction },
        new BoxCollider{
            AABB,
            glm::vec3(-config::PLAYER_WIDTH / 2, -config::PLAYER_HEIGHT / 2, -config::PLAYER_WIDTH / 2),
            glm::vec3(config::PLAYER_WIDTH / 2, config::PLAYER_HEIGHT / 2, config::PLAYER_WIDTH / 2)
        }
    ) {}

Player::~Player() {}

const std::string& Player::getName() const {
    return name;
}

void Player::setName(const std::string& playerName){
    name = playerName;
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

void Player::handleKeyboardInput(std::string action) {
    // variable for projection
    vec3 moveDirection = body.getDirection();
    mat4 transform = mat4(1.0f);
    vec3 axis = vec3(0, 1, 0);
    float angle = glm::radians(90.0f);

    if (action == "move_forward") {
        moveDirection = moveDirection;
    } else if (action == "move_backward") {
        moveDirection = -moveDirection;
    } else if (action == "strafe_left") {
        // project onto 90 degree left rotation
        moveDirection = vec3(rotate(transform, angle, axis) * vec4(moveDirection, 0.0f));
    } else if (action == "strafe_right") {
        // project onto 90 degree right rotation
        moveDirection = vec3(rotate(transform, -angle, axis) * vec4(moveDirection, 0.0f));
    } else if (action == "jump" && abs(body.getVelocity().y) < 1e-6f) {
        // if grounded, jump
        body.setVelocity(vec3(body.getVelocity().x, config::PLAYER_SPEED*0.5, body.getVelocity().z));
    } else {
        return;
    }
    
    moveDirection = normalize(glm::vec3(moveDirection.x, 0.0f, moveDirection.z));
    body.setVelocity(body.getVelocity() + moveDirection * config::PLAYER_SPEED);
}

void Player::handleMouseInput(glm::vec3 direction) {
    body.setDirection(direction);
}
