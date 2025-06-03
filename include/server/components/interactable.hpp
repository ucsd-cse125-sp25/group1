#pragma once
#include "components/object.hpp"
#include "components/room.hpp"
#include "player.hpp"
#include <vector>

class Player;
class Object;

class Interactable : public Object {
  public:
    Interactable(int id);
    Interactable(); // Default constructor, initializes with an invalid ID
    virtual ~Interactable() = default;
    void interact(const Player& player); // calls the overriden handleInteract function.
    void addRoom(Room* room);            // Adds a room to the interactable's list of rooms

  protected:
    virtual void handleInteract(
        const Player& player) = 0; // Pure virtual function, must be implemented by derived classes
    std::vector<Room*> roomPtrs;
};
