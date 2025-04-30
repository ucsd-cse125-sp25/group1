#pragma once

class Interactable
{
public:
    Interactable();
    virtual ~Interactable() = default;
    void interact(); //handles the input that riggers the handle event. 

protected:
    virtual void handleInteract() = 0; //Pure virtual function, must be implemented by derived classes
};