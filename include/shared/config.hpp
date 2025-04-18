#pragma once

#include <glm/vec3.hpp>

namespace config {
    inline constexpr const char* SERVER_IP = "127.0.0.1";
    inline constexpr int SERVER_PORT = 1111;

    inline constexpr int MAX_PLAYERS = 4;

    inline constexpr float WORLD_WIDTH = 1600.0f;
    inline constexpr float WORLD_HEIGHT = 900.0f;

    inline constexpr float FOVY = 45.0f;
    inline constexpr float NEAR = 0.1f;
    inline constexpr float FAR  = 100.0f;

    inline constexpr glm::vec3 CAMERA_OFFSET = glm::vec3(0.0f, 1.8f, 0.0f);

    inline constexpr glm::vec3 PLAYER_SPAWNS[4] = {
        { -2.0f, 0.0f,  2.0f },
        {  2.0f, 0.0f,  2.0f },
        { -2.0f, 0.0f, -2.0f },
        {  2.0f, 0.0f, -2.0f } 
    };
}
