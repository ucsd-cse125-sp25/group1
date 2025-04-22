#pragma once
#include <vector>
#include <string>
#include "Interactable.h"
#include "Coord.h"

class Room
{
public:
    // Todo: add constructor and destructor
    //Room(int id, const std::string& name = "Room");
    Room(int id, Coord topLeft, int w, int h);

    // Todo: add room functions and attributes
    void addInteractable(Interactable* object);
    void removeInteractable(Interactable* object);
    void draw(std::vector<std::vector<char>>& grid) const;
    bool contains(int x, int y) const;


    int getID() const;
    std::string getName() const;
    const std::vector<Interactable*>& getInteractables() const;


    
private:
    // Todo: add member variables
    int roomID;
    std::string roomName;
    // Todo: change these interactable pointers to unique_ptr rather than normal pointers to prevent mem leaks and make ownership clear
    std::vector<Interactable*> interactables;

    Coord topLeft;
    int width, height;

};