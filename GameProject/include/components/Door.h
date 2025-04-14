#pragma once
#include "Interactable.h"

class Door: public Interactable
{
public:
	
    // Todo: add constructor and destructor
    Door(bool locked, bool open, int destinationRoomId);
    ~Door() override;
    void interact() override;
    // Todo: add a mapper to which room the door leads to

    int getDestinationRoomID() const; // Accessor for the room it leads to
    bool isLocked();

private:
	bool _isLocked;
    bool isOpen;
    int destinationRoomId;
};