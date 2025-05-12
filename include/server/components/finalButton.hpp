#pragma once
#include "finalDoor.hpp"

class FinalButton {
public:
    FinalButton(int buttonID, int playerID, FinalDoor* door);
    ~FinalButton();

    // Check if the button is pressed
    bool isPressed() const;

    void pressButton();
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
    FinalDoor* door; // Pointer to the associated door
    bool pressed; // State of the button (pressed or not)
};