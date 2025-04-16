#pragma once

class Interactable
{
public:
    Interactable(bool unlocks = false, bool opens = false, bool closes = false, bool moves = false);
    // Todo: implement destructor
    virtual ~Interactable() = default;
    // Todo: add more functions
    virtual void interact() = 0; //Pure virtual function, 
protected:
    // Todo: add any other attributes, then update constructor
	bool canUnlock;
    bool canOpen;
    bool canClose;
    bool canMove;
};