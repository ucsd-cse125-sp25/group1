#pragma once
#include "components/interactable.hpp"

#include <functional>
#include <string>
#include <vector>

/**
 * Client Side FinalDoor Class
 * Client needs to be able to add keys to the door
 * However this interaction should be handled by the server
 * The server should be the one to determine if the door is locked or not
 * Client side mainly needs code for graphics and animation
 */
class FinalDoor : public Interactable {
  public:
    /**
     * Door should have constructor for how many keys is needed
     * Does it also need param for rigid body?
     * @param numKeys Number of keys required to unlock the door
     */
    FinalDoor(int numKeys);

    // Destructor
    ~FinalDoor();

    // Check if the door is locked
    bool isLocked() const;

    //---------------------------------------
    // Would these mainly be used to call animation sequences?
    //----------------------------------------

    /**
     * Unlock and open the door
     * This will be called by the last final button
     * When the last button is pressed door will be unlocked
     */
    void unlockAndOpen();

    // returns how many keys are currently held
    int getKeyCount() const;

    // add a key to the door
    // This is an interaction with the door
    // Should call server to add key
    void addKey(int keyID);

    /**
     * Checks if all keys are present
     * Buttons will check for this when they are pressed
     * @return true if all keys are present, false otherwise
     */
    bool canUnlock();

  private:
    int numKeys; // Number of keys required to unlock the door
    bool locked;
    bool unlockable; // If all keys are present
    // std::vector<std::string> keys; // Stores keys with their indices
    // corresponding to their positions
    int keyCount;                // Number of keys currently held
    std::vector<bool> keyStates; // This will be initiated with the number of keys
};
