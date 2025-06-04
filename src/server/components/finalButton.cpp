#include "components/finalButton.hpp"
#include "json.hpp"
#include "server.hpp"

using json = nlohmann::json;

// Constructor
FinalButton::FinalButton(int buttonID, int playerID, FinalDoor* door)
    : Interactable(buttonID), buttonID(buttonID), playerID(playerID), door(door) {
    // Initialize any member variables if needed
}

// Destructor
FinalButton::~FinalButton() {
    // Clean up resources if necessary
}

bool FinalButton::isPressed() const {
    return pressed;
}

void FinalButton::handleInteract(Player& player) {
    // Define behavior here
    if (player.getID() != playerID) {
        // If the player ID does not match, do not allow interaction
        return;
    }
    if (!pressButton())
        return;
    json message;
    // message["type"] = "sfx";
    // message["sfx_id"] = config::SWAMP_AUDIO_FILE;
    message["type"] = "final_button_pressed";
    message["client_id"] = player.getID();
    message["action"] = "interact";

    std::string packet = message.dump() + "\n";
    door->getLobby()->getServer().broadcastMessage(packet);
}

/**
 * should be called when button is pressed
 * Is this called when client side button is pressed?
 * Client side will broadcast message to server
 */
bool FinalButton::pressButton() {
    // Can only press button when all keys are present
    if (!door->canUnlock()) {
        return false; // Cannot press the button if the door is not unlockable
    }
    pressed = true;
    updateDoorState();
    return true; // Button pressed successfully
}

void FinalButton::updateDoorState() {
    // Let finalDoor know that the button was pressed
    door->updateButtonState(buttonID, true);
    if (door->canOpen()) {
        door->unlockAndOpen();
    }
}
