#pragma once
#include "finalDoor.hpp"

class finalButton {
public:
    finalButton(int buttonID, int playerID, finalDoor* door);
    ~finalButton();

    // Check if the button is pressed
    bool isPressed() const;

    /**
     * Buttonpressed()
     * 
     * updateButtonStates
     * Check if unlockable 
     * And unlock()
     * open()
     * When the final button is pressed door will be unlocked
     */

    // Let finalDoor know that the button was pressed
    void updateDoorState();

private:
    int buttonID; // ID of the button
    int playerID; // ID of the player who pressed the button
    finalDoor* door; // Pointer to the associated door
    bool pressed; // State of the button (pressed or not)
};