#include "components/finalDoor.hpp"

// Constructor
FinalDoor::FinalDoor(int numKeys) : Interactable(), numKeys(numKeys), keyStates(numKeys, false) {
    // Initialize any member variables if needed
}

// Destructor
FinalDoor::~FinalDoor() {
    // Clean up resources if necessary
}

// Open the door
void FinalDoor::unlockAndOpen() {
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
        unlockable = true;
    }
    return unlockable;
}