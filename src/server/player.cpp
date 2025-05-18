#include "player.hpp"

Player::Player(int playerID, Room* room, glm::vec3 position, glm::vec3 direction)
    : 
    id(playerID),
    curRoom(room),
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

Room* Player::getCurRoom() const {
    return curRoom;
}

void Player::setCurRoom(Room* room) {
    curRoom = room;
}

RigidBody& Player::getBody() {
    return body;
}

void Player::handleMovementInput(std::string action) {
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
        return;
    } else {
        return;
    }
    
    moveDirection = normalize(glm::vec3(moveDirection.x, 0.0f, moveDirection.z));
    body.setVelocity(body.getVelocity() + moveDirection * config::PLAYER_SPEED);
}

void Player::handleMouseInput(glm::vec3 direction) {
    body.setDirection(direction);
}

void Player::handleGeneralInput(std::string action) {
    if (action == "interact") {
        Interactable* interactable = this->isNearInteractable();
        if (interactable != nullptr) interactable->interact(*this);
    } else {
        return;
    }
}

Interactable* Player::isNearInteractable() {
    if (this->getCurRoom() == nullptr) return nullptr;

    std::vector<Interactable*> interactables = this->getCurRoom()->getInteractables();
    RigidBody* playerBody = &this->getBody();

    // Find closest interactable
    Interactable* closestInteractable = nullptr;
    // maximum distance needed to interact with an object
    float closestDistance = config::PLAYER_INTERACT_RANGE;
    for (Interactable* obj : interactables) {
        RigidBody* objBody = &(static_cast<Object *>(obj)->getBody());

        if (playerBody == objBody) continue;

        // Compare to minimum distance
        float currentDistance = glm::distance(playerBody->getPosition(), objBody->getPosition());
        if (currentDistance < closestDistance) {
            closestInteractable = obj;
            closestDistance = currentDistance;
        }
    }

    return closestInteractable;
}

void Player::customCollision(ICustomPhysics* otherObject) {}
