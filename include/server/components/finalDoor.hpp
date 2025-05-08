#pragma once

#include <string>
#include <functional>
#include <vector>

/**
 * Server Side FinalDoor Class
 * The server should be the one to determine if the door is locked or not
 * Should handle the buttons being pressed as well 
 * Should be also an interactable object
 */
class finalDoor {
public:
    /**
     * Door should have constructor for how many keys is needed
     * Does it also need param for rigid body?
     * @param numKeys Number of keys required to unlock the door
     */
    finalDoor(int numKeys);

    // Destructor
    ~finalDoor();

    // Check if the door is locked
    bool isLocked() const;

    //---------------------------------------
    // Used for game logic
    //----------------------------------------

    // Unlock the door
    void unlock(); 

    // Open the door
    void open();

    // returns how many keys are currently held
    int getKeyCount() const;

    // add a key to the door
    void addKey(); 

    bool canUnlock();

private:
    int numKeys; // Number of keys required to unlock the door
    bool locked;
    bool canUnlock; //If all keys are present and button States
    //std::vector<std::string> keys; // Stores keys with their indices corresponding to their positions
    int keyCount; // Number of keys currently held
    //int keyStates; 
    //int buttonPressed; // Number of buttons pressed 
    //std::unordered_map<int, bool> buttonStates; // Maps button IDs to their pressed state (true/false)
    int buttonStates[4]; // Button states (pressed or not pressed) - 4 buttons
    int keyStates[]; //This will be initiated with the number of keys
    //int array

};
