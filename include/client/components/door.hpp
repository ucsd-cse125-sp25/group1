#pragma once
#include "components/interactable.hpp"

class Door : public Interactable {
  public:
    /**
     * @brief Creates a door instance.
     *
     * Door does not need to know keyID on the client, since all unlocking logic
     * is handled on the server. Instead, a boolean isLocked is provided to initialize it.
     * Therefore, there is only one door constructor on the client.
     *
     * @param doorID the id of the door.
     * @param room1 the id of one of the rooms the door connects.
     * @param room2 the id of the other room the door connects.\
     * @param isLocked whether the door has a lock.
     */
    Door(int doorID, int room1, int room2, bool isLocked);
    ~Door() = default;

    /**
     * @brief Get the room id of the other side of the door from the player.
     *
     * Given the current room a player is in, return the other room that the door connects to.
     * Most likely useful when optimizing the physics by room or graphics rendering.
     *
     * @param currRoomID the id of the room the player is currently in.
     * @return int The roomID of the other room.
     */
    int getDestinationRoomID(int currRoomID) const;

    bool isLocked() const;
    bool isOpen() const;

    /**
     * @brief Let server know that a given player is trying to interact with the door.
     *
     * Sends a message to the server to call the server side's handleInteract.
     * The server then sends back whether the attempt to open the door was successful.
     * Upon receiving that message, `tryOpen()` should be called.
     *
     * @param player a reference to the player that is interacting with the door.
     */
    void sendInteractRequest(int playerID) override;

    /**
     * @brief given the server's interaction response, open the door or keep it closed.
     *
     * Receives a message from the server about whether the interaction (opening) was successful.
     * Call tryOpen() with the given state.
     * @param state whether the door can be opened successfully.
     */
    void processInteractResult(bool state) override;

  private:
    /**
     * @brief Open (or fail to open) the door.
     *
     * After receiving a message from the server of whether handleInteract successfully opened
     * the door, call tryOpen(true) if the door should open successfully or tryOpen(false)
     * otherwise. This will update instance variables if needed and play the appropriate animation.
     *
     * @param success Whether the door opens successfully.
     */
    void tryOpen(bool success);

    /**
     * @brief Helper function: opens door and plays animation
     */
    void openDoor();

    /**
     * @brief Helper function: unlocks door and plays animation
     */
    void unlockDoor();

    int doorID;
    bool locked;
    bool open;
    int rooms[2];
};
