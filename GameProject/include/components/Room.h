#pragma once
#include <vector>
#include <string>
#include "Interactable.h"

class Room
{
public:
    // Todo: add constructor and destructor
    Room(int id, const std::string& name = "Room");

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
    // Todo: change these interactable pointers to unique_ptr rather than normal pointers to prevent mem leaks and make ownership clear
    std::vector<Interactable*> interactables;

};