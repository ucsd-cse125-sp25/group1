#include "client.hpp"
#include <iostream>

int main() {
    Client client;

    if (!client.init()) {
        std::cerr << "Failed to initialize client.\n";
        return 1;
    }

    AudioManager audioManager;
    if (!audioManager.initialize()) {
        return 1; // Exit if FMOD fails
    }


    client.run();

    return 0;
}
