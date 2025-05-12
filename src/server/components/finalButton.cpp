#include "components/finalDoor.hpp"

// Constructor
FinalButton::FinalButton(int buttonID, int playerID, FinalDoor* door) {
    // Initialize any member variables if needed
    this->buttonID = buttonID;
    this->playerID = playerID;
    this->door = door;
}

// Destructor
FinalButton::~FinalButton() {
    // Clean up resources if necessary
}

bool FinalButton::isPressed() const {
    return pressed;
}

/**
 * should be called when button is pressed
 * Is this called when client side button is pressed?
 * Client side will broadcast message to server
 */
void FinalButton::pressButton() {
    //Can only press button when all keys are present
    if (!door->canUnlock()) {
        return; // Cannot press the button if the door is not unlockable
    }
    pressed = true;
    updateDoorState();
}

void FinalButton::updateDoorState() {
    // Let finalDoor know that the button was pressed
    door->addKey(buttonID);
    if (door->canOpen()) {
        door->unlockAndOpen();
    }
}



