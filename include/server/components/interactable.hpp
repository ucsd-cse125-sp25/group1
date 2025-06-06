#pragma once
#include <vector>
#include "components/object.hpp"
#include "components/room.hpp"
#include "player.hpp"

class Player;
class Object;

class Interactable : public Object {
  public:
    Interactable(int id);
    Interactable(); // Default constructor, initializes with an invalid ID
    virtual ~Interactable() = default;
    void interact(Player& player); // calls the overriden handleInteract function.
    void addRoom(Room* room);      // Adds a room to the interactable's list of rooms

  protected:
    virtual void handleInteract(
        Player& player) = 0; // Pure virtual function, must be implemented by derived classes
    std::vector<Room*> roomPtrs;
};
