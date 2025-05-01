#pragma once
#include "player.hpp"

class Interactable
{
public:
    Interactable();
    virtual ~Interactable() = default;
    void interact(const Player &player); //handles the input that triggers the handle event. 

protected:
    virtual void handleInteract(const Player &player) = 0; //Pure virtual function, must be implemented by derived classes
};