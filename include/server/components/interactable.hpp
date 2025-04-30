#pragma once

class Interactable
{
public:
    Interactable();
    virtual ~Interactable() = default;
    // Todo: add more functions
    void interact(); //handles the input that triggers the handle event. 

protected:
    virtual void handleInteract() = 0; //Pure virtual function, must be implemented by derived classes
};