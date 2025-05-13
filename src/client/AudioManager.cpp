#include <iostream>
#include "fmod_studio.hpp"

class audioManager {
public:
    FMOD::Studio::System* system = nullptr;

    bool initialize() {
        FMOD_RESULT result = FMOD::Studio::System::create(&system); // Create FMOD Studio System
        if (result != FMOD_OK) {
            std::cerr << "FMOD error! (" << result << ") Initialization failed." << std::endl;
            exit(-1);
        }

        // Initialize FMOD Studio, which will also initialize FMOD Core
        result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
        if (result != FMOD_OK) {
            std::cerr << "FMOD error! (" << result << ") Initialization failed." << std::endl;
            exit(-1);
        }

        std::cout << "FMOD successfully initialized!" << std::endl;
        return true;
    }

    void shutdown() {
        if (system) {
            system->release();
        }
    }
};