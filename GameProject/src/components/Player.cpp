#include "components/Player.h"

Player::Player(const std:: string& playerName, Coord coordinates)
    : name(playerName), position(coordinates)  // initialize member variables with parameters
{
    // Todo: init facingDirection variable
}

Player::~Player(){
    // Nothing todo yet; free any dynamically allocated in the future if added.
}

// Todo: add destructor

Coord Player::getPosition() const{
    // return shallow copy of position
    return Coord {position.x, position.y, position.z};
}

void Player::setPosition(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;
    // Todo: update facingDirection Variable
}

void Player::move(float x, float y){
    // Todo: smoothly move to x, y (w/ physics?) -- needs to call Server API to actually move there.
}

void Player::moveForward(){
    // Todo: use private `facingDirection` variable with private `move()` to implement this
}

void Player::moveBackward(){
    // Todo: use private `facingDirection` variable with private `move()` to implement this
}

void Player::moveLeft(){
    // Todo: use private `facingDirection` variable with private `move()` to implement this
}

void Player::moveRight(){
    // Todo: use private `facingDirection` variable with private `move()` to implement this
}

void Player::turn(){
    // Todo: use private `facingDirection` variable with private `move()` to implement this
}

void Player::jump(){
    // TODO: update z position using physics logic
}