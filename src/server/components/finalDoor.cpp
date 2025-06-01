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
    // Open handled by final buttons
    // Broadcast message to all clients
}

int FinalDoor::getKeyCount() const {
    return keyCount;
}

void FinalDoor::addKey(int keyID) {
    keyCount++;
    keyStates[keyID] = true; // Mark the key as present
}

bool FinalDoor::canUnlock() {
    if (keyCount == numKeys) {
        unlockable = true;
    }
    return unlockable;
}

void FinalDoor::updateButtonState(int buttonID, bool pressed) {
    if (buttonID >= 0 && buttonID < 4) {
        buttonStates[buttonID] = pressed; // Update the state of the button
    }
}
bool FinalDoor::canOpen() {
    if (unlockable) {

        // Check if all buttons are pressed
        for (int i = 0; i < 4; ++i) {
            if (!buttonStates[i]) {
                return false; // If any button is not pressed, return false
            }
        }
        return true; // All buttons are pressed and all keys are present
    }
    return false;
}
