// Door.h
#pragma once
#include "Coord.h"
#include <vector>


class Door {
public:
    Door(Coord pos);
    void draw(std::vector<std::vector<char>>& grid) const;
    bool isAt(int x, int y) const;
    bool open();   // returns true if it was closed and now opened
    bool closed() const;
private:
    Coord position;
    bool locked = false;
    bool opened = false;
};
