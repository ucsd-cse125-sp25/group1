#include "components/Door.h"

// Todo: add other function definitions

Door::Door(bool isLocked, bool isOpen, int destRoomId)
    // Init interactions: Doors are always unlockable and openable, but not closeable or movable
    : Interactable(true, true, false, false),
      // init member variables for Door
      locked(isLocked),
      open(isOpen),
      destinationRoomId(destRoomId)
{
    // Todo: any additional setup if necessary
}

Door::~Door(){
    // Nothing todo yet; free any dynamically allocated in the future if added.
}

int Door::getDestinationRoomID() const{
    return destinationRoomId;
}

bool Door::isLocked() const{
    return locked;
}

bool Door::isOpen() const{
    return open;
}

// Todo: override interact() function