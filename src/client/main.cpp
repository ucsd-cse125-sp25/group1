#include <iostream>
#include "audioEngine.hpp"
#include "client.hpp"

int main() {
    Client client;

    if (!client.init()) {
        std::cerr << "Failed to initialize client.\n";
        return 1;
    }

    client.run();

    return 0;
}
