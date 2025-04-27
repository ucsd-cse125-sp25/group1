#include "../../include/components/Player.h"

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
    //return Coord {position.x, position.y, position.z};
    return position;
}

void Player::setPosition(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;
    // Todo: update facingDirection Variable
}

int Player::getCurRoomID() const {
    return curRoomID;
}

void Player::setCurRoomID(int roomID){
	curRoomID = roomID;
}

bool Player::move(int dx, int dy, std::vector<std::vector<char>>& map) {
    int nx = position.x + dx;
    int ny = position.y + dy;
    if (map[ny][nx] == '#') {
        return false;
    }
    position.x = nx; 
    position.y = ny;
    return true;
}

std::vector<int> Player::getKeys() const{
    return keys;
}

void Player::draw(std::vector<std::vector<char>>& map) const {
    map[position.y][position.x] = '@';
}

void Player::addKey(int keyID){
    keys.push_back(keyID);
}

bool Player::removeKey(int keyID){
    auto iterator = std::find(keys.begin(), keys.end(), keyID);
    if (iterator != keys.end()) {
        keys.erase(iterator);
        return true;  // removed
    }
    return false; // not found
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