#pragma once
#include "player.hpp"
#include "components/object.hpp"

class Player;

class Interactable : public Object
{
public:
    Interactable();
    virtual ~Interactable() = default;
    void interact(const Player &player); //calls the overriden handleInteract function.

protected:
    virtual void handleInteract(const Player &player) = 0; //Pure virtual function, must be implemented by derived classes
};