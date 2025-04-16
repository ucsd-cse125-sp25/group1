#pragma once
#include "Interactable.h"

class Door: public Interactable
{
public:
	
    // Todo: add constructor and destructor
    Door(bool isLocked, bool isOpen, int destinationRoomId);
    ~Door() override;
    void interact() override;
    // Todo: add a mapper to which room the door leads to

    int getDestinationRoomID() const; // Accessor for the room it leads to
    bool isLocked() const;
    bool isOpen() const;

private:
	bool locked;
    bool open;
    int destinationRoomId;
};