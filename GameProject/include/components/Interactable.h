#pragma once

class Interactable
{
public:
    Interactable();
    // Todo: implement destructor
    virtual ~Interactable() = default;
    // Todo: add more functions
    void interact() = 0; //handles the input that riggers the handle event. 

    virtual void handleInteract() = 0; //Pure virtual function, must be implemented by derived classes
};