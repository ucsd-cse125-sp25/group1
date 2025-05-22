#pragma once

#include "components/interactable.hpp"
#include <functional>
#include <string>
#include <vector>

/**
 * Server Side FinalDoor Class
 * The server should be the one to determine if the door is locked or not
 * Should handle the buttons being pressed as well
 * Should be also an interactable object
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
  // Used for game logic
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
  void addKey(int keyID);

  /**
   * Checks if all keys are present
   * Buttons will check for this when they are pressed
   * @return true if all keys are present, false otherwise
   */
  bool canUnlock();

  /**
   * @brief Check if the door can be opened
   * Door can be opened if all buttons are pressed
   * and all keys are present
   * @return true if the door can be opened, false otherwise
   */
  bool canOpen();

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
  bool buttonStates[4] = {
      false}; // Button states (pressed or not pressed) - 4 buttons
  std::vector<bool> keyStates; // This will be initiated with the number of keys
  // int array
};
