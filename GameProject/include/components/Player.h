#pragma once
#include <string>

struct Coord {
    float x;
    float y;
    float z;
};

class Player
{
public:
    // Todo: add constructor and destructor
    Player(const std:: string& playerName, Coord coordinates);
    ~Player();
    // Todo: add player functions and attributes

    Coord getPosition() const;
    /* sets position of player - used when they die and need to respawn somewhere */
    void setPosition(float x, float y, float z = 0);
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void turn();
    void jump();

    //get the player's current room ID. 
    int getCurRoomID() const;
    void setCurRoomID(int id);

private:
    // Todo: add private attributes and functions
    std::string name;
    Coord position; // Should the players world coordinates be an attribute? 
    //Include world coordinates for all objects and such as well?
    // Todo: add `facingDirection` variable that keeps track of where the player is facing.
    /* called internally by the public facing move functions */
    void move(float x, float y);

    int curRoomID; // ID of the room the player is currently in
};