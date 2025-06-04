#pragma once
#include "components/interactable.hpp"
#include "finalDoor.hpp"

/**
 * @brief Represents a button that can be pressed to control a FinalDoor in the game.
 *
 * The FinalButton class inherits from Interactable and is used to handle interactions
 * with the final button that unlocks the final door when all conditions are met.
 */
class FinalButton : public Interactable {
  public:
    /**
     * @brief Constructs a FinalButton object with a given button ID, player ID, and associated
     * door.
     *
     * Currently buttonID corresponds with the objectID from the map in server
     *
     * @param buttonID ID of the object
     * @param playerID ID of the player who should be pressing the button
     * @param door Pointer to the FinalDoor that this button controls
     */
    FinalButton(int buttonID, int playerID, FinalDoor* door);
    ~FinalButton();

    /**
     * @brief Checks if the button is currently pressed.
     *
     * @return true if the button is pressed, false otherwise.
     */
    bool isPressed() const;

    /**
     * @brief Handles interaction with the button by a player.
     *
     * Calls press button
     * Checks if the player ID matches the button's player ID.
     *
     * Then broadcasts message to all clients indicating the button was pressed.
     */
    void handleInteract(Player& player) override;

    /**
     * @brief Attempts to press the button.
     *
     * This function checks if the door can be unlocked (all keys present) before allowing the
     * button to be pressed. If the door is unlockable, it updates the button state and returns
     * true.
     *
     * @return true if the button was pressed successfully, false otherwise.
     */
    bool pressButton();
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
    /**
     * @brief Updates the state of the associated door when the button is pressed.
     * 
     * Will also check if the door can be opened
     * and if so, will unlock and open the door.
     */
    void updateDoorState();

  private:
    int buttonID;    // ID of the button
    int playerID;    // ID of the player who pressed the button
    FinalDoor* door; // Pointer to the associated door
    bool pressed;    // State of the button (pressed or not)
};
