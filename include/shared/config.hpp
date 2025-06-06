#pragma once

#include <glm/vec3.hpp>
#include <array>
#include <string>
#include <vector>

namespace config {
inline constexpr const char* SERVER_IP = "127.0.0.1";
inline constexpr int SERVER_PORT = 2399;
inline constexpr bool BYPASS = false;

inline constexpr float gravity = -20.0f;

inline constexpr int MAX_PLAYERS = 4;
inline constexpr int TICK_RATE = 30;

inline constexpr int TOTAL_GAME_TIME = 600; // 10 mins

inline constexpr float WORLD_WIDTH = 1600.0f;
inline constexpr float WORLD_HEIGHT = 900.0f;

// Camera
inline constexpr float FOVY = 45.0f;
inline constexpr float NEAR_CLIP = 0.1f;
inline constexpr float FAR_CLIP = 150.0f;

inline constexpr float MAX_PITCH = 89.0f;
inline constexpr float MIN_PITCH = -60.0f;

inline constexpr glm::vec3 CAMERA_OFFSET = {0.0f, 2.8f, 0.0f};

// Shadows
inline constexpr int SHADOW_MAP_RES_STATIC = 1024;
inline constexpr int SHADOW_MAP_RES_INTERACTABLE = 1024;
inline constexpr int SHADOW_MAP_RES_PLAYER = 1024;
inline constexpr float SHADOW_NEAR_CLIP = 0.1f;
inline constexpr float SHADOW_FAR_CLIP = 25.0f;
inline constexpr int SHADOW_TEXTURE_UNIT = 3;

// Players
inline constexpr glm::vec3 PLAYER_SPAWNS[4] = {
    {-3.0f, 0.0f, 3.0f}, {3.0f, 0.0f, 3.0f}, {-3.0f, 0.0f, -3.0f}, {3.0f, 0.0f, -3.0f}};

inline constexpr const char* PLAYER_CHARACTERS_IDLE[4] = {
    "../src/client/characters/cat_idle.fbx", "../src/client/characters/dog_idle.fbx",
    "../src/client/characters/frog_idle.fbx", "../src/client/characters/frog_idle.fbx"};

inline constexpr const char* PLAYER_CHARACTERS_RUN[4] = {
    "../src/client/characters/cat_run.fbx", "../src/client/characters/dog_run.fbx",
    "../src/client/characters/frog_run.fbx", "../src/client/characters/frog_run.fbx"};

inline constexpr float PLAYER_SPEED = 10.0f;
inline constexpr float PLAYER_WEIGHT = 10.0f;

inline constexpr float PLAYER_WIDTH = 1.53f;
inline constexpr float PLAYER_HEIGHT = 3.2f;
inline constexpr float PLAYER_DEPTH = 2.3f;

inline constexpr float PLAYER_INTERACT_RANGE = 5.0f;

inline constexpr float MOUSE_SENSITIVITY = 0.1f;

inline constexpr float CANNONBALL_SPEED = 100.0f;

// Model positions
inline constexpr glm::vec3 LOBBY_POSITION = {0.0f, 0.0f, 0.0f};

inline constexpr glm::vec3 HOTEL_ROOM_POSITIONS[15] = {
    {-150.0f, 0.0f, -50.0f}, {-150.0f, 0.0f, 10.0f}, {-130.0f, 0.0f, 30.0f}, {-30.0f, 0.0f, 10.0f},
    {-30.0f, 0.0f, 30.0f},   {30.0f, 0.0f, -50.0f},  {30.0f, 0.0f, 10.0f},   {30.0f, 0.0f, 30.0f},
    {50.0f, 0.0f, -10.0f},   {50.0f, 0.0f, 10.0f},   {50.0f, 0.0f, 30.0f},   {110.0f, 0.0f, -10.0f},
    {110.0f, 0.0f, 10.0f},   {130.0f, 0.0f, 10.0f},  {150.0f, 0.0f, 10.0f}};

inline constexpr glm::vec3 HOTEL_HALLWAY_POSITIONS[7] = {
    {-150.0f, 0.0f, -20.0f}, {-100.0f, 0.0f, 30.0f}, {-60.0f, 0.0f, 30.0f}, {-30.0f, 0.0f, -20.0f},
    {30.0f, 0.0f, -20.0f},   {80.0f, 0.0f, -10.0f},  {150.0f, 0.0f, -20.0f}};

inline constexpr glm::vec3 TABLE_POSITION = {5.0f, 0.0f, -5.0f};

inline constexpr glm::vec3 SWAMP_ROOM_POSITION = {-130.0f, 0.0f, -50.0f};
inline constexpr glm::vec3 FROG_POSITION = {7.0f, 0.0f, 4.0f};

inline constexpr glm::vec3 SWAMP_KEY_ROOM_POSITION = {-30.0f, 0.0f, -50.0f};
inline constexpr glm::vec3 SWAMP_KEY_POSITION = {0.0f, 1.0f, 0.0f};

inline constexpr glm::vec3 CIRCUS_ROOM_POSITION = {100.0f, 0.0f, -50.0f};

inline constexpr glm::vec3 CIRCUS_KEY_ROOM_POSITION = {150.0f, 0.0f, -50.0f};

inline constexpr glm::vec3 PIANO_ROOM_POSITION = {150.0f, 0.0f, 50.0f};

inline constexpr glm::vec3 PARKOUR_ROOM_POSITION = {-130.0f, 0.0f, 10.0f};
inline constexpr glm::vec3 PARKOUR_OBJECT_POSITIONS[3] = {
    {0.0f, -1.5f, 0.0f}, {2.5f, -0.5f, 0.0f}, {5.0f, 0.5f, 0.0f}};
inline constexpr glm::vec3 PARKOUR_KEY_POSITION = {-8.0f, 6.0f, 8.0f};

// Finaldoor
inline constexpr glm::vec3 FINALDOOR_KEY_SLOTS[4] = {
    {1.8f, 4.4f, 19.7f}, {0.3f, 4.3f, 19.5f}, {-1.2f, 4.4f, 19.7f}, {-2.7f, 4.4f, 19.7f}};
inline constexpr glm::vec3 FINALDOOR_LEFT_POSITION = {0.0f, 0.0f, 20.0f};
inline constexpr glm::vec3 FINALDOOR_RIGHT_POSITION = {0.0f, 0.0f, 20.0f};
inline constexpr glm::vec3 FINALDOOR_POSITION = {0.0f, 0.0f, 20.0f};
inline constexpr glm::vec3 BUTTON_BLUE_POSITION = {7.0f, 3.5f, 19.4f};
inline constexpr glm::vec3 BUTTON_PINK_POSITION = {-7.0f, 3.5f, 19.4f};
inline constexpr glm::vec3 BUTTON_GREEN_POSITION = {12.0f, 3.5f, 19.4f};
inline constexpr glm::vec3 BUTTON_YELLOW_POSITION = {-12.0f, 3.5f, 19.4f};
inline constexpr glm::vec3 BACK_PLATE_POSITIONS[4] = {
    {7.0f, 3.5f, 19.4f}, {-7.0f, 3.5f, 19.4f}, {12.0f, 3.5f, 19.4f}, {-12.0f, 3.5f, 19.4f}};

// Swamp Related Configs
inline constexpr glm::vec3 SWAMP_RESPAWN = {1.0f, 1.0f, 0.0f};
inline constexpr int SWAMP_NUM_ROWS = 8;

inline constexpr int SWAMP_NUM_LILYPADS = 16; // Total

inline const std::vector<int> SWAMP_SOLUTION = {0, 1, 1, 1, 0, 1, 1, 0};
inline constexpr const char* SWAMP_AUDIO_FILE = "{9b22e271-4a2c-47cd-8662-1a4f0ddee8de}";

inline constexpr int SWAMP_NUM_FIREFLIES = 150;

// Lobby related

// TODO: Adjust once rendered
inline constexpr float SWAMP_LILYPAD_WIDTH = 1.0f;
inline constexpr float SWAMP_LILYPAD_HEIGHT = 1.0f;

// Circus Related Configs
inline constexpr glm::vec3 CIRCUS_RESPAWN = {-35.0f, 1.0f, 0.0f};
inline constexpr int NUM_CANNONBALLS = 8;
inline constexpr glm::vec3 CANNONBALL_POSITIONS[NUM_CANNONBALLS] = {{30.0f, 3.0f, 16.0f},
                                                                    {30.0f, 3.0f, 12.0f},
                                                                    {30.0f, 3.0f, 8.0f},
                                                                    {30.0f, 3.0f, 4.0f},
                                                                    // {30.0f, 3.0f, 0.0f},
                                                                    {30.0f, 3.0f, -4.0f},
                                                                    {30.0f, 3.0f, -8.0f},
                                                                    {30.0f, 3.0f, -12.0f},
                                                                    {30.0f, 3.0f, -16.0f}};
// how long to wait before firing cannons after music stops
inline constexpr int SECONDS_CANNON_DELAY = 3;

// Sound effects
inline constexpr glm::vec3 PIANO_RESPAWN = {0.0f, 0.0f, -27.0f};

// TODO: Convert GUID to event names
inline constexpr const char* SWAMP_AMBIENCE_TRACK = "{25c216fb-36d9-42c9-bd0f-4662b826ff2a}";
inline constexpr const char* FOOTSTEPCARPET = "{5a18903c-2b5f-4fd0-b153-63a502130d90}";
inline constexpr const char* FOOTSTEPWOOD = "{4834907d-09e7-460e-b9f9-4f18b067acf0}";
inline constexpr const char* JUMPLILYPAD = "{85da62c4-60ce-4776-b1f3-2503b761aa8c}";
inline constexpr const char* UNLOCKDOOR = "{008e7455-ae30-40ce-a197-5e85b67035b8}";
inline constexpr const char* GRABKEY = "{f811c9cc-fec0-4714-8a32-e645ad8a502b}";
inline constexpr const char* WATERSPLASH = "{907b8e60-bc68-4a05-b2dc-394c92c13343}";
inline constexpr const char* CARNIVAL_AMBIENCE_TRACK = "{7251ffff-27b9-48ac-a1a8-da14ea95facb}";
inline constexpr const char* PIANO_AMBIENCE_TRACK = "{b77419f3-b86e-48af-bd48-945f3bfe1069}";
// Audio for Set Volume

// Controlled by Client
inline constexpr float SWAMP_AMBIENCE_VOL = 0.5f;
inline constexpr float CARNIVAL_AMBIENCE_VOL = 0.3f;
inline constexpr float PIANO_AMBIENCE_VOL = 0.3f;

inline constexpr float FOOTSTEPCARPET_VOL = 0.05f;
inline constexpr float FOOTSTEPWOOD_VOL = 0.05f;

inline constexpr int FOOTSTEP_COOLDOWN_RATE = 7;

// Controlled by Server
inline constexpr float SWAMP_AUDIO_FILE_VOL = 1.0f; // 2.5
inline constexpr float LILYPAD_VOL = 0.2f;
inline constexpr float UNLOCKDOOR_VOL = 0.4f; // 0.5
inline constexpr float GRABKEY_VOL = 0.2f;
inline constexpr float WATERSPLASH_VOL = 0.05f;
} // namespace config
