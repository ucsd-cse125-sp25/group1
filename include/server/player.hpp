/**
 * @file player.hpp
 * @brief Declaration of the Player class.
 *
 * This file contains the declaration of the Player class which contains all information about
 * the player, including their physics body and other attributes specific to a player.
 */
#pragma once
#include <string>
#include <set>
#include <glm/glm.hpp>
#include <vector>
#include "config.hpp"
#include "rigidBody.hpp"
#include "components/interactable.hpp"
#include "components/room.hpp"

class Interactable;
class Room;

class Player : public ICustomPhysics {
public:
    /**
     * @brief Constructs a Player object with a given player id, room ID, position, and direction.
     *
     * Initializes the player's rigid body at the specified position and orientation,
     * assigning it a box collider based on player configuration settings.
     * Sets the player ID and the ID of the room they're currently in.
     * 
     * @param playerID ID of the player
     * @param roomID ID of the room the player initially belongs to.
     * @param position Initial position of the player.
     * @param direction Initial facing direction of the player.
     */
    Player(int playerID, Room* room, glm::vec3 position, glm::vec3 direction);
    ~Player();
    
    /**
     * @brief Returns the name of the player.
     *
     * @return The player's name as a string.
     */
    const std::string& getName() const;

    /**
     * @brief Sets the player's name.
     *
     * @param playerName The new name for the player.
     */
    void setName(const std::string& playerName);

    /**
     * @brief Returns the reference of the room the player is currently in.
     *
     * @return Current room as a pointer.
     */
    Room* getCurRoom() const;

    /**
     * @brief Sets the player's current room ID.
     *
     * @param roomID The new room ID to assign to the player.
     */
    void setCurRoom(Room* room);

    /**
     * @brief Returns the set of key IDs the player possesses.
     *
     * @return std::set<int> A copy of the player's key ID list.
     */
    const std::set<int>& getKeyIDs() const {
        return keyIDs;
    }

    /**
     * @brief Adds a key to the player's inventory.
     *
     * @param keyID ID of the key to add.
     */
    void addKey(int keyID) {
        keyIDs.insert(keyID);
    }

    /**
     * @brief Removes a key from the player's inventory.
     *
     * Searches for the given key ID and removes it if found.
     *
     * @param keyID ID of the key to remove.
     * @return true if the key was found and removed; false otherwise.
     */
    bool removeKey(int keyID){
        bool found = keyIDs.erase(keyID) > 0;
        return found;
    }

    /**
     * @brief Returns a reference to the player's rigid body.
     *
     * @return Reference to the player's associated RigidBody instance.
     */
    RigidBody& getBody();

    /**
     * @brief Handles player movement input actions by adjusting the player's velocity accordingly.
     *
     * Processes movement commands ("move_forward", "move_backward", "strafe_left", "strafe_right")
     * by projecting the player's movement direction onto the appropriate axis and applying
     * a horizontal velocity change based on the configured player speed.
     *
     * Processes the "jump" command by applying an upward velocity if the player is grounded
     * (i.e., has near-zero vertical velocity).
     *
     * Any unrecognized actions are ignored.
     *
     * @param action String representing the player action to handle.
     */
    void handleMovementInput(std::string action);

    /**
     * @brief Updates the player's facing direction based on mouse input.
     *
     * @param direction A 3D vector indicating the new direction the player should face.
     */
    void handleMouseInput(glm::vec3 direction);


    /**
     * @brief Handles general player actions such as interaction.
     *
     * If the action is "interact" and the player is near an interactable object,
     * the player will interact with it.
     *
     * @param action A string representing the type of player action (e.g., "interact").
     */
    void handleGeneralInput(std::string action);

    /**
     * @brief Determines the nearest interactable object within interaction range.
     *
     * Iterates over all interactable objects in the current room and returns a pointer
     * to the closest one, as long as it is within a defined maximum distance. Returns
     * nullptr if no interactable is nearby or if the player is not in a room.
     *
     * @return Interactable* Pointer to the nearest interactable object, or nullptr if none.
     */
    Interactable* getNearestInteractable();

    void customCollision(ICustomPhysics* otherObject) override;

private:
    int id;
    std::string name;
    Room* curRoom;
    RigidBody body;
    std::set<int> keyIDs; // Keys (by ID) the player has collected
};