#pragma once

#include <glm/vec3.hpp>
#include <array>
#include <string>
#include <vector>

namespace config {
    inline constexpr const char* SERVER_IP = "127.0.0.1";
    inline constexpr int SERVER_PORT = 1111;

    inline constexpr int MAX_PLAYERS = 4;
    inline constexpr int TICK_RATE = 30;

    inline constexpr int TOTAL_GAME_TIME = 600; // 10 mins

    inline constexpr float WORLD_WIDTH = 1600.0f;
    inline constexpr float WORLD_HEIGHT = 900.0f;

    inline constexpr float FOVY = 45.0f;
    inline constexpr float NEAR_CLIP = 0.1f;
    inline constexpr float FAR_CLIP = 120.0f;

    inline constexpr float MAX_PITCH = 89.0f;
    inline constexpr float MIN_PITCH = -89.0f;

    inline constexpr glm::vec3 CAMERA_OFFSET = {0.0f, 3.0f, 0.0f};

    inline constexpr glm::vec3 PLAYER_SPAWNS[4] = {
        {-3.0f, 1.0f, 3.0f}, {3.0f, 1.0f, 3.0f}, {-3.0f, 1.0f, -3.0f}, {3.0f, 1.0f, -3.0f}};

    // Remove this when we stop using cubes for characters
    inline constexpr glm::vec3 PLAYER_COLORS[4] = {glm::vec3(1.0f, 0.8f, 0.9f),
                                                   glm::vec3(1.0, 0.78, 0.62), glm::vec3(0.8, 0.7, 1.0),
                                                   glm::vec3(0.75, 0.9, 1.0)};

    inline constexpr float PLAYER_SPEED = 10.0f;
    inline constexpr float PLAYER_WEIGHT = 10.0f;
    inline constexpr float PLAYER_WIDTH = 1.0f;
    inline constexpr float PLAYER_HEIGHT = 1.0f;
    inline constexpr float PLAYER_DEPTH = 1.0f;
    inline constexpr float PLAYER_INTERACT_RANGE = 10.0f;

    inline constexpr float MOUSE_SENSITIVITY = 0.1f;

    // Model positions
    inline constexpr glm::vec3 HOTEL_ROOM_POSITION = {0.0f, 0.0f, 0.0f};
    inline constexpr glm::vec3 TABLE_POSITION = {0.0f, 0.0f, 0.0f};
    inline constexpr glm::vec3 SWAMP_ROOM_POSITION = {20.0f, 0.0f, 0.0f};

    // Swamp Related Configs
    inline constexpr glm::vec3 SWAMP_RESPAWN = {21.0f, 1.0f, 0.0f};
    inline constexpr int SWAMP_NUM_ROWS = 8;

    inline constexpr int SWAMP_NUM_LILYPADS = 16; // Total

    inline const std::vector<int> SWAMP_SOLUTION = {0, 1, 0, 1, 0, 1, 0, 1};
    inline constexpr const char* SWAMP_AUDIO_FILE = "solution_audio.mp3";

    inline constexpr int SWAMP_NUM_FROGS = 3;

    // TODO: Adjust once rendered
    inline constexpr float SWAMP_LILYPAD_WIDTH = 1.0f;
    inline constexpr float SWAMP_LILYPAD_HEIGHT = 1.0f;

    // TODO: Convert GUID to event names
    inline constexpr const char* SWAMP_AMBIENCE_TRACK = "{25c216fb-36d9-42c9-bd0f-4662b826ff2a}";
    inline constexpr const char* footstepCarpet = "{5a18903c-2b5f-4fd0-b153-63a502130d90}";
    inline constexpr const char* footstepWood = "{4834907d-09e7-460e-b9f9-4f18b067acf0}";
    inline constexpr const char* jumpLilyPad = "{85da62c4-60ce-4776-b1f3-2503b761aa8c}";
    inline constexpr const char* unlockDoor = "{008e7455-ae30-40ce-a197-5e85b67035b8}";

} // namespace config
