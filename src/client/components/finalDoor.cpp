#include "components/finalDoor.hpp"

// Constructor
FinalDoor::FinalDoor(int numKeys) : Interactable() {
    // Initialize any member variables if needed
    this->numKeys = numKeys;
    this->keyStates = new bool[numKeys];
}

// Destructor
FinalDoor::~FinalDoor() {
    // Clean up resources if necessary
}

// Open the door
void FinalDoor::open() {
    //Open handled by final buttons
    //Broadcast message to all clients
}

int FinalDoor::getKeyCount() const {
    return keyCount;
}

void FinalDoor::addKey(int keyID) {
    keyCount++;
    keyStates[keyID] = true; // Mark the key as present

}

/**
 * Checks if all keys are present
 * Buttons will check for this when they are pressed
 * @return true if all keys are present, false otherwise
 */
bool FinalDoor::canUnlock() {
    if (keyCount == numKeys) {
        canUnlock = true;
    }
    return canUnlock;
}