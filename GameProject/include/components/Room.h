#pragma once
#include <vector>
#include <string>
#include "Interactable.h"

class Room
{
public:
    // Todo: add constructor and destructor
    Room(int roomID, const std::string& name = "Room");

    // Todo: add room functions and attributes
    void addInteractable(Interactable* object);
    void removeInteractable(Interactable* object);

    int getID() const;
    std::string getName() const;
    const std::vector<Interactable*>& getInteractables() const;


    
private:
    // Todo: add member variables
    int roomID;
    std::string roomName;
    std::vector<Interactable*> interactables;

};