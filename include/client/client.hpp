#pragma once

#include <boost/asio.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "json.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "scene.hpp"
#include "shader.hpp"

/**
 * @brief Handles client-side networking, input, and rendering.
 * 
 * Connects to the server, processes player input and server updates,
 * manages the local scene, and renders the game view.
 */
class Client {
public:
    /**
     * @brief Constructs a Client instance and initializes the TCP socket.
     */
    Client();

    /**
     * @brief Destroys the Client instance.
     */
    ~Client();

    /**
     * @brief Initializes the client by connecting to the server.
     * 
     * Internally calls connectToServer().
     * 
     * @return true if the connection is successful, false otherwise.
     */
    bool init();

    /**
     * @brief Main execution method for the client.
     * 
     * Initializes the window, OpenGL context, and scene,
     * then enters the main game loop and performs cleanup.
     */
    void run();

    /**
     * @brief First-person camera representing the player's view.
     */
    Camera camera;

    bool isMouseLocked;     // True if the mouse is locked inside the window.

    double lastMouseX;      // Last mouse X position.
    double lastMouseY;      // Last mouse Y position.
    bool isFirstMouse;      // True if this is the first mouse movement. (Helps avoid a big jump when starting.)

    float yaw;              // Left-right rotation of the camera.
    float pitch;            // Up-down rotation of the camera.

private:
    /**
     * @brief Establishes connection to the server and receives client ID.
     * 
     * @return true if successful, false otherwise.
     */
    bool connectToServer();

    /**
     * @brief Reads a complete message from the server and forwards it to handleServerMessage().
     */
    void receiveServerMessage();

    /**
     * @brief Handles server messages from the server.
     * 
     * Parses a JSON message and dispatches it based on its "type" field.
     * Supported message types:
     * - "player_states": Updates player positions, directions, and handles disconnected players.
     * - "time_left": Updates the game timer displayed on the client.
     * 
     * @param message A newline-terminated JSON string received from the server.
     */
    void handleServerMessage(const std::string& message);

    /**
     * @brief Updates the local player states based on server data.
     * 
     * Updates each player's state in the local data structures,
     * and sets the current client's camera position.
     * Also detects players who have disconnected, removes their data from local data structures,
     * and marks them for removal from the scene.
     * 
     * @param parsed A parsed JSON object containing player state information.
     */
    void updatePlayerStates(const nlohmann::json& parsed);

    void updateGameTimer(const nlohmann::json& parsed);

    /**
     * @brief Handles real-time player input and sends actions to the server.
     * 
     * Checks for specific key presses (WASD and arrow keys), maps them to movement actions,
     * and constructs a JSON message containing the active actions. If any actions are detected,
     * the message is sent to the server for processing.
     * 
     * @param window Pointer to the GLFW window used to poll key input.
     */
    void handleKeyboardInput(GLFWwindow* window);

    /**
     * @brief Sends the player's facing direction to the server based on the current yaw.
     * 
     * If the mouse is locked, this function:
     * - Converts the current yaw value into a normalized direction vector.
     * - Creates a "mouse_input" JSON message containing the direction.
     * - Sends the message to the server to update the player's facing direction.
     * 
     * Does nothing if the mouse is currently unlocked.
     */
    void handleMouseInput();

    /**
     * @brief Sends a message to the server over the TCP socket.
     * 
     * @param message A JSON message to send to the server.
     */
    void sendMessageToServer(const nlohmann::json& message);

    /**
     * @brief Initializes the GLFW window and OpenGL.
     * 
     * @return true if successful, false otherwise.
     */
    bool initWindow(GLFWwindow*& window);

    /**
     * @brief Sets basic OpenGL settings.
     */
    void initGL();

    /**
     * @brief Initializes the scene and sets up the player camera.
     * 
     * Creates the scene instance and positions the camera for a first-person view,
     * based on the client's spawn location and an initial viewing direction.
     */
    void initScene();

    /**
     * @brief Main game loop for updates and rendering.
     */
    void gameLoop(GLFWwindow* window);

    /**
     * @brief Cleans up GLFW resources.
     */
    void cleanup(GLFWwindow* window);

    boost::asio::io_context ioContext;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;

    boost::asio::streambuf buffer;

    int clientId;

    std::unordered_map<int, glm::vec3> playerPositions;
    std::unordered_map<int, glm::vec3> playerDirections;

    std::unordered_set<int> disconnectedIds;

    std::unique_ptr<Scene> scene;
};
