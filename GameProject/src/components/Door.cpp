#include "components/Door.h"
#include <cassert>

// Todo: add other function definitions
Door::Door(int doorID, int room1, int room2, int keyID)
    : Interactable(),
    locked(keyID != -1),
    open(false)
{
    rooms[0] = room1;
    rooms[1] = room2;
}

Door::Door(int doorID, int room1, int room2)
    : Door(doorID, room1, room2, -1){}

Door::~Door(){
    // Nothing todo yet; free any dynamically allocated in the future if added.
}

int Door::getDestinationRoomID(int currRoomID) const{
    if (currRoomID == rooms[0]){
        return rooms[1];
    }
    if (currRoomID == rooms[1]){
        return rooms[0];
    }
    assert(false && "currRoomID must be one of the rooms the door connects!");
}

bool Door::isLocked() const{
    return locked;
}

bool Door::isOpen() const{
    return open;
}

// Todo: override interact() function