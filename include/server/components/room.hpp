#pragma once
#include <vector>
#include <string>
#include <memory> 
#include "components/interactable.hpp"

class Room
{
public:
    Room(int id, const std::string& name = "Room");
    ~Room();
    void addInteractable(std::unique_ptr<Interactable> object);
    void removeInteractable(Interactable* object);

    int getID() const;
    std::string getName() const;
    std::vector<Interactable*> getInteractables() const;
    
private:
    int roomID;
    std::string roomName;
    std::vector<std::unique_ptr<Interactable>> interactables;
};