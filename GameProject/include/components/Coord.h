#pragma once

// A simple 3D coordinate struct, with default to (0,0,0)
struct Coord {
    int x;
    int y;
    int z;

    // Constructor with optional parameters
    Coord(int xVal = 0, int yVal = 0, int zVal = 0)
        : x(xVal), y(yVal), z(zVal) {}
};