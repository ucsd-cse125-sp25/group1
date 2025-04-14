#pragma once

class Interactable
{
public:
    Interactable(/* Todo: add parameters */bool canUnlock = false, bool canOpen = false, bool canClose = false, bool canMove = false);
    // Todo: update constructor and add destructor
    virtual ~Interactable() = default;
    // Todo: add attributes and functions
    virtual void interact() = 0; //Pure virtual function, 
protected:
	bool canUnLock;
    bool canOpen;
    bool canClose;
    bool canMove;
};