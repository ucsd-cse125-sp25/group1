#pragma once
#include <glm/glm.hpp>
#include "components/interactable.hpp"
#include "player.hpp"
#include "rigidBody.hpp"

class Server; 

class Door : public Interactable {
  public:
    // NOTE: first index is ALWAYS the negative most side of the door
    Door(int doorID, int room1, int room2, Server& serverRef );            // doors without locks
    Door(int doorID, int room1, int room2, int keyID, Server& serverRef); // locked doors
    ~Door() = default;

    bool isLocked() const;
    bool isOpen() const;
    void setRoomZones(RigidBody* room1, RigidBody* room2);
    int getRoomID(int index) const;

  protected:
    /**
     * @brief Have the given player attempt to open the door.
     *
     * If the door is unlocked, the player can successfully open the door.
     * If the door is locked and player has the key, the player can open the door.
     * If the door is locked but the player doesn't have the key, the door remains locked.
     *
     */
    void handleInteract(const Player& player) override;

  private:
    void openDoor(int playerId);
    void unlockDoor();
    int keyID;
    bool locked;
    bool open;
    int rooms[2];
    RigidBody* roomZones[2] = {nullptr, nullptr};
    Server& server;
};
