#pragma once
#include "Interactable.h"

class Door: public Interactable
{
public:
    // Todo: add constructor and destructor
    Door(int doorID, int room1, int room2 /*TODO: add rigidBody for server*/); // doors without locks
    Door(int doorID, int room1, int room2, int keyID /*TODO: add rigidBody for server*/); // locked doors
    ~Door();
    void interact();
    int getDestinationRoomID(int currRoomID) const; // Accessor for the room it leads to
    bool isLocked() const;
    bool isOpen() const;
private:
    int doorID;
	bool locked;
    bool open;
    int rooms[2];
};