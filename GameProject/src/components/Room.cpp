#include "../../include/components/Room.h"

// Todo: add function definitions
// Room::Room(int id, const std::string& name)
//     : roomID(id), roomName(name)
// {
//     // Todo: any additional initialization (doors?) if needed
// }
Room::Room(int id, Coord tl, int w, int h)
 : roomID(id), topLeft(tl), width(w), height(h) {}

// Room::~Room(){
//     // Nothing todo yet; free any dynamically allocated in the future if added.
// }

void Room::draw(std::vector<std::vector<char>>& grid) const {
    int x0 = topLeft.x, y0 = topLeft.y;
    int x1 = x0 + width - 1, y1 = y0 + height - 1;
    // Draw horizontal walls
    for(int x = x0; x <= x1; ++x) {
        grid[y0][x] = '#';
        grid[y1][x] = '#';
    }
    // Draw vertical walls
    for(int y = y0; y <= y1; ++y) {
        grid[y][x0] = '#';
        grid[y][x1] = '#';
    }
}

int Room::getID() const{
    return roomID;
}


bool Room::contains(int x, int y) const {
    return x >= topLeft.x && x < topLeft.x+width
        && y >= topLeft.y && y < topLeft.y+height;
}

std::string Room::getName() const{
    return roomName;
}

void Room::addInteractable(Interactable* object){
    interactables.push_back(object);
}

// Todo: add getInteractables, removeInteractable functions