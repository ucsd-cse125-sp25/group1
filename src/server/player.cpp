#include "player.hpp"

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
        },
        this
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

void Player::handleKeyboardInput(const std::vector<std::string> actions) {
    // variable for projection
    vec3 moveDirection = glm::vec3(0.0f);
    mat4 transform = mat4(1.0f);
    vec3 axis = vec3(0, 1, 0);
    float angle = glm::radians(90.0f);

    // handle horizontal movement
    if (std::find(actions.begin(), actions.end(), "move_forward") != actions.end()) {
        moveDirection += body.getDirection();
    }
    if (std::find(actions.begin(), actions.end(), "move_backward") != actions.end()) {
        moveDirection -= body.getDirection();
    }
    if (std::find(actions.begin(), actions.end(), "strafe_left") != actions.end()) {
        // project onto 90 degree left rotation
        moveDirection += vec3(rotate(transform, angle, axis) * vec4(body.getDirection(), 0.0f));
    }
    if (std::find(actions.begin(), actions.end(), "strafe_right") != actions.end()) {
        // project onto 90 degree right rotation
        moveDirection += vec3(rotate(transform, -angle, axis) * vec4(body.getDirection(), 0.0f));
    }

    // flatten on xz plane and normalize all horizontal movement
    if (length(moveDirection) > 1e-6f)
        moveDirection = normalize(glm::vec3(moveDirection.x, 0.0f, moveDirection.z));

    // add jump if inputted
    if ((std::find(actions.begin(), actions.end(), "jump") != actions.end()) && (abs(body.getVelocity().y) < 1e-6f)) {
        // if grounded, jump
        moveDirection.y = 0.5f;
    }
    
    body.setVelocity(body.getVelocity() + moveDirection * config::PLAYER_SPEED);
}

void Player::handleMouseInput(glm::vec3 direction) {
    body.setDirection(direction);
}

void Player::customCollision(ICustomPhysics* otherObject) {}
