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

class Client {
public:
    /**
     *  @brief Constructs the Client object and initialize TCP  
     */
    Client();

    /**
     *  @brief Destructor for the Client object
     */
    ~Client();

    /**
     *  @brief Verifies initializations are setup
     * 
     * Verifies connection to server 
     * 
     * @return true if initialized correctly, false otherwise
     */
    bool init();

    /**
     *  @brief Main Execution method for Client 
     * 
     * initializes window, GL, Scence
     */
    void run();

    /**
     *  @brief Camera object representing player's cur position
     */
    Camera camera;

private:
    /**
     *  @brief Sets up the connection with server
     * 
     * Connects to server, sets ClientId to Id received from server
     * 
     * @return true, if successfully connected to server, false otherwise
     */
    bool connectToServer();

    /**
     *  @brief Receive and extracts message from server and pass to handleServerMessage
     * 
     * Ensures valid Socket and attempts to read message from server and extract message
     * 
     */
    void receiveServerMessage();

    /**
     *  @brief Handles the Message received from the Server
     * 
     * Based on the "type" value of the messaged received from the server, 
     *  resolve the server message accordingly
     *
     * @param message A JSON string containing updates from the server
     */
    void handleServerMessage(std::string message);

    /**
     *  @brief Watch for Player inputs, and if sends input to   
     * 
     *  Keys checked:
     * - W / Up Arrow --> move_forward
     * - S / Down Arrow  --> move_backward
     * - A / Left Arrow  --> strafe_left
     * - D / Right Arrow --> strafe_right
     * 
     * sends JSON string packet of { type: "input", actions : [array of acctions] } to server
     * 
     *  @param window Pointer to the active GLFW window used to query key states.
     */
    void handlePlayerInput(GLFWwindow* window);

    /**
     *  @brief Creates the Packed to send the provided message to the server
     *
     *  @param message A JSON string containing updates to send to server
     */
    void sendMessageToServer(const nlohmann::json& message);

    /**
     *  @brief Initializes GLFW Window
     * 
     *  @return true, if GLFW window successfully initialized, false otherwise
     */
    bool initWindow(GLFWwindow*& window);

    /**
     *  @brief Initializes GL
     */
    void initGL();

    /**
     *  @brief Initializes the Scene
     * 
     * Initialize the scence with camera at client's position
     */
    void initScene();

    /**
     *  @brief Main game rendering and update loop for 
     */
    void gameLoop(GLFWwindow* window);
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
