#include <iostream>
#include "server.hpp"

int main() {
    Server server;

    if (!server.init()) {
        std::cerr << "Failed to initialize server.\n";
        return 1;
    }

    server.run();

    return 0;
}
