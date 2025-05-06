// Door.h
#pragma once
#include "Coord.h"
#include <vector>


// class Door {
// public:
//     Door(Coord pos, bool lock, bool open);
//     bool open();   // returns true if it was closed and now opened
//     bool closed() const;
// private:
//     Coord position;// Position of the door in world coordinates
   
//     std::vector<int> roomIDPair;
//     bool locked;
//     bool opened;
// };

#include "Interactable.h"

class Door: public Interactable
{
public:
    // Todo: add constructor and destructor
    Door(int doorID, int room1, int room2, int keyID /*TODO: add rigidBody for server*/); // locked doors
    Door(int doorID, int room1, int room2 /*TODO: add rigidBody for server*/); // doors without locks

    ~Door();
    void interact();
    int getDestinationRoomID(int currRoomID) const; // Accessor for the room it leads to
    bool isLocked() const;
    bool isOpen() const;
    
    void handleInteract() override;



    //ONLY FOR ASCII FUNCTIONS
    Door(int doorID, int room1, int room2, int keyID, Coord pos); //For testing
    Door(int doorID, int room1, int room2, Coord pos /*TODO: add rigidBody for server*/); // doors without locks

    void draw(std::vector<std::vector<char>>& grid) const;
    //bool isAt(int x, int y) const;
    bool unlockDoor(std::vector<int> keys);
    bool openDoor();
    bool isAt(int x, int y) const;


private:
    int doorID;
    int keyID;
    Coord position;// Position of the door in world coordinates this will be in rigid body
     // Use room room[0] as reference point for the door
    // Should also have position of the door relative to the rooms? No, just one gobal value
    // Rooms should share 1 door object... Render these separately, or render this together 
	bool locked;
    bool open;
    int rooms[2];
};
