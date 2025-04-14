#pragma once
#include <string>

struct Coord {
    float x;
    float y;
};
class Player
{
public:
    // Todo: add constructor and destructor
    Player(const std:: string& name);
    ~Player();
    // Todo: add player functions and attributes
private:
    // Todo: add member variables
    std::string name;
    Coord position; // Should the players world coordinates be an attribute? 
    //Include world coordinates for all objects and such as well?
};