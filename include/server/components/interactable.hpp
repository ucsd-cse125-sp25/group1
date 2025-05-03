#pragma once
#include "player.hpp"

class Interactable
{
public:
    Interactable();
    virtual ~Interactable() = default;
    void interact(const Player &player); //calls the overriden handleInteract function.

protected:
    virtual void handleInteract(const Player &player) = 0; //Pure virtual function, must be implemented by derived classes
};