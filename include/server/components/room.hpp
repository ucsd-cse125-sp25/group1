#pragma once
#include <memory>
#include <string>
#include <vector>
#include "components/interactable.hpp"

class Interactable;

class Room {
  public:
    Room(int id, const std::string& name = "Room");
    ~Room();
    void addInteractable(Interactable* object);
    void removeInteractable(Interactable* object);

    int getID() const;
    std::string getName() const;
    std::vector<Interactable*> getInteractables() const;

  private:
    int roomID;
    std::string roomName;
    std::vector<Interactable*> interactables;
};
