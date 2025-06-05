#include "components/finalDoor.hpp"
#include "lobby.hpp"
#include "server.hpp"
#include "json.hpp"

using json = nlohmann::json;
// Constructor
FinalDoor::FinalDoor(int numKeys, int objectID, Lobby* lobbyRef)
    : Interactable(objectID), numKeys(numKeys), keyStates(numKeys, false), lobby(lobbyRef) {
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
    json message;

    message["type"] = "final_door_open"; // This is game ending

    // How can we broadcast this message to all clients?
    std::string packet = message.dump() + "\n";
    lobby->getServer().broadcastMessage(packet);
}

void FinalDoor::handleInteract(Player& player) {
    // Add keys from player to the door
    std::set<int> playersKeys = player.getKeyIDs();
    if (playersKeys.empty()) {
        // If the player has no keys, do nothing
        // Or do no key sound effect?
        return;
    }
    for (int val : playersKeys) {
        addKey(val);           // Add keys from player to the door
        player.removeKey(val); // Remove keys from player
        // Or should each interact only add one key?
        break; // Assuming we only want to add one key at a time
    }

    json message;
    message["type"] = "final_door_interact";
    // message["sfx_id"] = config::Some sound effect ID;
    message["client_id"] = player.getID();
    message["action"] = "interact";
    message["slot_id"] = getKeyCount() - 1; // Include the current key count
    message["room"] = "lobby"; // Include the room name

    std::string packet = message.dump() + "\n";
    lobby->getServer().broadcastMessage(packet);
}

int FinalDoor::getKeyCount() const {
    return keyCount;
}

void FinalDoor::addKey(int keyID) {
    if (keyID < 0 || keyID >= numKeys || keyStates[keyID]) {
        // If the key ID is invalid or the key is already present, do nothing
        return; // Invalid key ID
    }
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

Lobby* FinalDoor::getLobby() {
    return lobby;
}
