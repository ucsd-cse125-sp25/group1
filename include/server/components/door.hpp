#pragma once
#include <glm/glm.hpp>
#include "rigidBody.hpp"
#include "player.hpp"
#include "server/components/interactable.hpp"

class Door: public Interactable
{
public:
    // Todo: add constructor and destructor
    Door(int doorID, int room1, int room2, glm::vec3 position, glm::vec3 direction); // doors without locks
    Door(int doorID, int room1, int room2, int keyID, glm::vec3 position, glm::vec3 direction); // locked doors
    ~Door() = default;

    /**
     * @brief Have the given player attempt to open the door.
     * 
     * If the door is unlocked, the player can successfully open the door.
     * If the door is locked and player has the key, the player can open the door.
     * If the door is locked but the player doesn't have the key, the door remains locked.
     * 
     */
    int getDestinationRoomID(int currRoomID) const; // Accessor for the room it leads to
    bool isLocked() const;
    bool isOpen() const;
protected:
    void handleInteract(const Player& player) override;
private:
    void openDoor();
    void unlockDoor();
    int doorID;
    int keyID;
	bool locked;
    bool open;
    int rooms[2];
};