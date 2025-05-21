#include "swamp.hpp"
#include <iostream>

Swamp::Swamp(int roomID, std::string audioFile) : Room(roomID), audioFile(audioFile) {}

Swamp::~Swamp() {
    // Destructor
    std::cout << "Swamp Room destructor \n" << std::endl;
}

// only the person that presses e on the frog hears the audio (then server doesn't need to know)