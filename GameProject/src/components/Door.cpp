// Door.cpp
#include "../../include/components/Door.h"

Door::Door(Coord pos) : position(pos) {}

void Door::draw(std::vector<std::vector<char>>& grid) const {
    char c = opened ? '/' : '+';
    grid[position.y][position.x] = c;
}

bool Door::isAt(int x, int y) const {
    return position.x == x && position.y == y;
}

// Try to open: succeeds if not already opened and not locked
bool Door::open() {
    if (!opened && !locked) {
        opened = true;
        return true;
    }
    return false;
}

bool Door::closed() const { return !opened; }