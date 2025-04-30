#pragma once

#include <boost/asio.hpp>
#include <deque>
#include <glm/glm.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "world.hpp"
#include "player.hpp"

/**
 * @brief Handles server-side networking and world updates for a multiplayer game.
 * 
 * Accepts client connections, processes client messages,
 * updates player states, and broadcasts updates to all connected clients.
 */
class Server {
public:
    /**
     * @brief Constructs a Server instance.
     * 
     * Initializes the networking components and prepares the server for client connections.
     */
    Server();

    /**
     * @brief Destroys the Server instance.
     */
    ~Server();

    /**
     * @brief Initializes the server.
     * 
     * Prints IP and port information, and adds a floor to the world.
     * 
     * @return true.
     */
    bool init();

    /**
     * @brief Runs the server's main event loop.
     * 
     * Starts accepting client connections, ticking the server at a fixed rate,
     * and processing networking events.
     */
    void run();

private:
    /**
     * @brief Finds an available client ID.
     * 
     * Searches for a free slot in the clients map.
     * 
     * @return Available client ID if found, otherwise -1.
     */
    int findAvailableId();

    /**
     * @brief Starts accepting new client connections asynchronously.
     * 
     * Upon connection, assigns client IDs and sets up listening.
     */
    void acceptConnections();

    /**
     * @brief Handles client joining logic.
     * 
     * Sends the assigned client ID to the client and spawns a new player in the world.
     * 
     * @param clientId The ID assigned to the newly connected client.
     */
    void handleClientJoin(int clientId);

    /**
     * @brief Handles client disconnection logic.
     * 
     * Cleans up resources associated with a client when they disconnect.
     * 
     * @param clientId The ID of the disconnecting client.
     */
    void handleClientDisconnect(int clientId);

    /**
     * @brief Listens for incoming messages from a client.
     * 
     * Reads data asynchronously and queues messages for later processing.
     * 
     * @param clientId The ID of the client to listen to.
     */
    void listenToClient(int clientId);

    /**
     * @brief Starts the server ticking loop.
     * 
     * At a fixed interval, processes client messages, physics updates, and broadcasts states.
     */
    void startTick();

    /**
     * @brief Handles all queued messages from clients.
     * 
     * Processes keyboard and mouse input for each player.
     */
    void handleClientMessages();

    /**
     * @brief Advances the physics simulation.
     * 
     * Steps the physics world and resolves collisions.
     */
    void handlePhysics();

    /**
     * @brief Sends updated player states to all connected clients.
     * 
     * Includes player positions and directions.
     */
    void broadcastPlayerStates();

    /**
     * @brief Starts the game timer.
     * 
     * Begins ticking the server-side game timer, broadcasting the remaining time
     * to all connected clients every second. This function is called once 4 clients
     * are connected and continues running until all clients disconnect.
     */
    void startGameTimer();

    /**
     * @brief Broadcasts the current time left to all clients.
     * 
     * Sends a JSON message containing the remaining game time (in minutes and seconds)
     * to every connected client. Called once per second by the game timer loop.
     */
    void broadcastTimeLeft();

    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::acceptor acceptor;

    boost::asio::steady_timer tickTimer;
    boost::asio::steady_timer gameTimer;

    bool hasTimerStarted;
    int timeLeft;

    std::unordered_map<int, std::shared_ptr<boost::asio::ip::tcp::socket>> clients;
    std::unordered_map<int, boost::asio::streambuf> buffers;

    World world;
    std::unordered_map<int, Player *> players;

    std::unordered_map<int, std::deque<std::string>> clientMessages;
};
