#pragma once

struct Coord {
    float x;
    float y;
    float z;
};

class Object
{
public:
    Object(Coord position /*TODO: add graphics*/);
    ~Object();
private:
    // TODO: add graphics
};