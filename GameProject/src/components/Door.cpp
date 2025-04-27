// // Door.cpp
#include "../../include/components/Door.h"

// Door::Door(Coord pos, bool locked, bool open) 
//         : position(pos),  locked(locked), opened(open) {}

// void Door::draw(std::vector<std::vector<char>>& grid) const {
//     char c = opened ? '/' : '+';
//     grid[position.y][position.x] = c;
// }

// bool Door::isAt(int x, int y) const {
//     return position.x == x && position.y == y;
// }

// // Try to open: succeeds if not already opened and not locked
// bool Door::open() {
//     if (!opened && !locked) {
//         opened = true;
//         return true;
//     }
//     return false;
// }

// bool Door::closed() const { return !opened; }

//#include "components/Door.h"
#include <cassert>

// Todo: add other function definitions
Door::Door(int doorID, int room1, int room2, int keyID)
    : Interactable(),
    locked(keyID != -1),
    open(false)
{
    rooms[0] = room1;
    rooms[1] = room2;
}

Door::Door(int doorID, int room1, int room2)
    : Door(doorID, room1, room2, -1){}

Door::Door(int doorID, int room1, int room2, int keyID, Coord pos) 
    : Interactable(), doorID(doorID), keyID(keyID), position(pos) {
        rooms[0] = room1;
        rooms[1] = room2;
        open = false;
        locked = true;
    } //For testing
Door::~Door(){
    // Nothing todo yet; free any dynamically allocated in the future if added.
}

void Door::handleInteract() {
    // your existing interact() logic, or call interact()
}


void Door::draw(std::vector<std::vector<char>>& grid) const {
    char c = open ? '=' : '/';
    grid[position.y][position.x] = c;
    if (grid[position.y+1][position.x] == ' ') grid[position.y-1][position.x] = c;
    else if (grid[position.y-1][position.x] == ' ') grid[position.y+1][position.x] = c;
    else if (grid[position.y][position.x+1] == ' ') grid[position.y][position.x-1] = c;
    else if (grid[position.y][position.x-1] == ' ') grid[position.y][position.x+1] = c;
}

bool Door::isAt(int x, int y) const {
    return position.x == x && position.y == y;
}

int Door::getDestinationRoomID(int currRoomID) const{
    if (currRoomID == rooms[0]){
        return rooms[1];
    }
    if (currRoomID == rooms[1]){
        return rooms[0];
    }
    assert(false && "currRoomID must be one of the rooms the door connects!");
}

bool Door::isLocked() const{
    return locked;
}

bool Door::isOpen() const{
    return open;
}

bool Door::openDoor() {
    if (!open && !locked) {
        open = true;
        return true;
    }
    return false;
}

bool Door::unlockDoor(std::vector<int> keys) {
    auto iterator = std::find(keys.begin(), keys.end(), keyID);
    if (iterator != keys.end()) {
        locked = false;
        return true;  // unLocked
    }
    return false; 
}


// Todo: override interact() function