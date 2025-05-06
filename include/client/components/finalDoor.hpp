#pragma once

#include <string>
#include <functional>
#include <vector>

/**
 * Client Side FinalDoor Class
 * Client needs to be able to add keys to the door
 * However this interaction should be handled by the server
 * The server should be the one to determine if the door is locked or not
 * Client side mainly needs code for graphics and animation
 */
class FinalDoor {
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
    //Would these mainly be used to call animation sequences?
    //----------------------------------------

    // Unlock the door
    void unlock(); 

    // Open the door
    void open();

    // returns how many keys are currently held
    int getKeyCount() const;

    // add a key to the door
    void addKey(); 

private:
    int numKeys; // Number of keys required to unlock the door
    bool locked;
    bool canUnlock; //If all keys are present
    //std::vector<std::string> keys; // Stores keys with their indices corresponding to their positions
    int keyCount; // Number of keys currently held
};
