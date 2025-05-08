#pragma once

#include "Room.h"
#include <vector>
#include <string>

class Hallway : public Room {
public:
    Hallway(const std::string& name,
        double length,
        double width,
        char orientation
        );

    
}