#pragma once

#include <functional>
#include <string>
#include <vector>
#include "components/interactable.hpp"

class Lobby; // Forward declaration of Lobby class

/**
 * Server Side FinalDoor Class
 * The server should be the one to determine if the door is locked or not
 * Should handle the buttons being pressed as well
 * Should be also an interactable object
 *
 * Two distinctions to be made, door is LOCKED while keys are not present
 * Door is UNLOCKED when all keys are present
 * Door is OPEN when the last button is pressed
 */
class FinalDoor : public Interactable {
  public:
    /**
     * Door should have constructor for how many keys is needed
     * Does it also need param for rigid body?
     * @param numKeys Number of keys required to unlock the door
     * @param objectID ID of the object in the server's map, do we want to use this?
     * @param lobbyRef Reference to the Lobby where the door is located
     */
    FinalDoor(int numKeys, int objectID, Lobby* lobbyRef);

    // Destructor
    ~FinalDoor();

    /**
     * @brief Returns whether the door is currently locked.
     *
     * @return true if the door is locked, false otherwise.
     */
    bool isLocked() const;

    //---------------------------------------
    // Used for game logic
    //----------------------------------------

    /**
     * Update the state of a button
     *
     * Called by FinalButton when it is pressed
     * @param buttonID ID of the button being updated
     * @param pressed True if the button is pressed, false otherwise
     */
    void updateButtonState(int buttonID, bool pressed);

    /**
     * Unlock and open the door
     * This will be called by the last final button
     * When the last button is pressed door will be unlocked
     *
     * Broadcast message to indicate game is ending, door is deleted?
     */
    void unlockAndOpen();

    /**
     * @brief Returns the number of keys
     *
     * @return int Number of keys .
     */
    int getKeyCount() const;

    /**
     * Adds a key to the door
     * This will be called by the player when they interact with the door
     * @param keyID ID of the key being added
     */
    void addKey(int keyID);

    /**
     * Checks if all keys are present
     * Buttons will check for this when they are pressed
     * @return true if all keys are present, false otherwise
     */
    bool canUnlock();

    /**
     * @brief Updates the door's state based on button presses.
     *
     * This function checks if the door can be opened based on the current button states
     * and key count, and updates the door's locked state accordingly.
     */
    void handleInteract(Player& player) override;

    /**
     * @brief Check if the door can be opened
     * Door can be opened if all buttons are pressed
     * and all keys are present
     * @return true if the door can be opened, false otherwise
     */
    bool canOpen();

    Lobby* getLobby();

  private:
    int numKeys; // Number of keys required to unlock the door
    bool locked;
    bool unlockable; // If all keys are present and button States
    // std::vector<std::string> keys; // Stores keys with their indices
    // corresponding to their positions
    int keyCount; // Number of keys currently held
    // int keyStates;
    // int buttonPressed; // Number of buttons pressed
    // std::unordered_map<int, bool> buttonStates; // Maps button IDs to their
    // pressed state (true/false)
    bool buttonStates[4] = {false}; // Button states (pressed or not pressed) - 4 buttons
    std::vector<bool> keyStates;    // This will be initiated with the number of keys
                                    // int array
    Lobby* lobby;                   // Reference to the lobby where the door is located
};
