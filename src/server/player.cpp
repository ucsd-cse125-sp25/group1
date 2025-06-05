#include "player.hpp"

Player::Player(int playerID, int roomID, glm::vec3 position, glm::vec3 direction, World* world)
    : id(playerID), curRoomID(roomID),
      body(glm::vec3(0.0f), glm::vec3(0.0f), config::PLAYER_WEIGHT,
           new Transform{position, direction},
           new BoxCollider{AABB, glm::vec3(-config::PLAYER_WIDTH / 2, 0, -config::PLAYER_DEPTH / 2),
                           glm::vec3(config::PLAYER_WIDTH / 2, config::PLAYER_HEIGHT,
                                     config::PLAYER_DEPTH / 2)},
           this, world) {}

Player::~Player() {}

const std::string& Player::getName() const {
    return name;
}

void Player::setName(const std::string& playerName) {
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

void Player::handleMovementInput(const std::vector<std::string> actions) {
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
    if ((std::find(actions.begin(), actions.end(), "jump") != actions.end()) &&
        (abs(body.getVelocity().y) < 1e-6f)) {
        // if grounded, jump
        moveDirection.y = 0.5f;
        jumpSfxCooldown = false;
    }

    body.setVelocity(body.getVelocity() + moveDirection * config::PLAYER_SPEED);
}

void Player::handleMouseInput(glm::vec3 direction) {
    body.setDirection(direction);
}

void Player::handleGeneralInput(const std::vector<std::string> actions,
                                Interactable* interactable) {
    if (std::find(actions.begin(), actions.end(), "interact") != actions.end()) {
        if (interactable != nullptr)
            interactable->interact(*this);
    } else {
        return;
    }
}

Interactable* Player::getNearestInteractable(Room* room) {
    if (room == nullptr)
        return nullptr;

    std::vector<Interactable*> interactables = room->getInteractables();
    RigidBody* playerBody = &this->getBody();

    // Find closest interactable
    Interactable* closestInteractable = nullptr;
    // maximum distance needed to interact with an object
    float closestDistance = config::PLAYER_INTERACT_RANGE;
    for (Interactable* obj : interactables) {
        RigidBody* objBody = obj->getBody();

        if (playerBody == objBody)
            continue;

        // Compare to minimum distance
        float currentDistance = glm::distance(playerBody->getPosition(), objBody->getPosition());

        if (currentDistance < closestDistance) {
            closestInteractable = obj;
            closestDistance = currentDistance;
        }
    }

    return closestInteractable;
}

int Player::getID() const {
    return id;
}

bool Player::getJumpSfxCooldown() const {
    return jumpSfxCooldown;
}

void Player::setJumpSfxCooldown(bool value) {
    jumpSfxCooldown = value;
}

void Player::customCollision(ICustomPhysics* otherObject) {}
