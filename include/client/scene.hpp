#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <player.hpp>
#include <GLFW/glfw3.h>
#include <map>
#include <memory>
#include <unordered_map>
#include "animatedModel.hpp"
#include "animator.hpp"
#include "camera.hpp"
#include "canvas.hpp"
#include "config.hpp"
#include "cube.hpp"
#include "firefly.hpp"
#include "fireflyRenderer.hpp"
#include "json.hpp"
#include "model.hpp"
#include "modelInstance.hpp"
#include "pointLight.hpp"
#include "shader.hpp"
#include "shadowMap.hpp"

/**
 * @brief Manages the 3D scene, including models and player entities.
 *
 * Handles loading shaders, setting up models, updating player states,
 * and rendering the complete scene.
 */
class Scene {
  public:
    /**
     * @brief Constructs a Scene instance.
     * @param playerID Player ID.
     */
    Scene(int playerID);

    /**
     * @brief Destroys the Scene instance.
     */
    ~Scene();

    /**
     * @brief Initializes the scene.
     *
     * Loads shaders and models required for rendering.
     */
    void init();

    /**
     * @brief Updates a player's position and direction.
     *
     * If the player does not exist, adds a new player.
     *
     * @param id Player ID.
     * @param position New position.
     * @param direction New facing direction.
     */
    void updatePlayerState(int id, const glm::vec3& position, const glm::vec3& direction);

    /**
     * @brief Removes a player from the scene.
     *
     * @param id Player ID to remove.
     */
    void removePlayer(int id);

    /**
     * @brief Removes a child instance from a specific room in the scene.
     *
     * @param roomName The name of the room containing the instance.
     * @param type The type/category of the instance to remove (e.g., "lilypad").
     * @param id The unique ID of the instance to remove.
     */
    void removeInstanceFromRoom(const std::string& roomName, const std::string& type, int id);

    /**
     * @brief Removes a door from using a global ID.

     * @param id Global door ID.
     */
    void removeDoor(int id);

    void addKeyToSlot(const std::string& roomName, const std::string& type, int id);

    /**
     * @brief Renders shadow maps for static geometry.
     *
     * This is called only once when the scene initializes.
     */
    void renderStaticShadowPass();

    /**
     * @brief Renders shadow maps for interactable geometry.
     *
     * This is called only once when the scene initializes.
     */
    void renderInteractableShadowPass();

    /**
     * @brief Renders shadow maps for lilypad objects in the swamp room.
     *
     * If 'id' is -1 (default), renders all lilypads by splitting them across two shadow maps.
     * Otherwise, renders only the shadow map responsible for the given lilypad ID.
     *
     * @param id Lilypad ID to render shadow map for, or -1 for all.
     */
    void renderLilypadShadowPass(int id = -1);

    /**
     * @brief Marks an interactable shadow map as active or inactive.
     *
     * This flag is passed to the fragment shader to skip sampling from unused shadow cubemaps,
     * which helps avoid unnecessary texture lookups and improves performance.
     *
     * @param roomName Name of the room (e.g., "keyRoom").
     * @param index Index of the shadow map to mark.
     * @param isActive True to enable sampling; false to skip it in the shader.
     */
    void setInteractableShadowActive(std::string roomName, int index, bool isActive) {
        interactableShadowActive[roomName][index] = isActive;
    };

    /**
     * @brief Renders the entire scene.
     *
     * Draws static models and dynamic player cubes.
     *
     * @param camera The active camera providing view and projection matrices.
     * @param boundingBoxMode If true, draws bounding boxes for debugging.
     */
    void render(const Camera& camera, bool boundingBoxMode);

    void updateWindow();

    GLFWwindow* window;
    std::unique_ptr<Canvas> canvas;

    /**
     * @brief Sets roomID of the given client ID
     *
     * @param clientID The ID of the client.
     * @param roomID to be set
     *
     */
    void setPlayerRoomID(int clientID, int roomID);

    /**
     * @brief Gets roomID of the given client ID
     *
     * @param clientID The ID of the client.
     * @return int The player ID.
     */
    int getPlayerRoomID(int clientID);

    /**
     * @brief Sets player character's animation state
     *
     * @param clientID client ID.
     * @param state 0: idle, 1: run
     */
    void setPlayerState(int clientID, int state);

  private:
    /**
     * @brief Sets up rooms and the objects they contain.
     *
     * Adds models to the scene in a hierarchy–
     * for example, a room as the parent and its objects as children.
     * Called when the scene is initialized.
     */
    void initRooms();

    /**
     * @brief Initializes point lights per room.
     */
    void initLights();

    /**
     * @brief Initializes shadow maps for all point lights.
     */
    void initShadowMaps();

    /**
     * Creates and stores a given number of fireflies with random positions, directions,
     * speeds, and sizes inside a defined bounding area.
     *
     * @param count Number of fireflies to spawn.
     */
    void spawnFireflies(int count);

    int playerID;

    std::vector<std::string> roomNames;
    std::unordered_map<std::string, std::unordered_set<std::string>> connectedRooms;

    std::unordered_map<std::string, std::vector<PointLight>> pointLights;
    std::unordered_map<std::string, std::vector<std::unique_ptr<ShadowMap>>> staticShadowMaps;
    std::unordered_map<std::string, std::vector<std::unique_ptr<ShadowMap>>> interactableShadowMaps;
    std::unordered_map<std::string, std::vector<bool>> interactableShadowActive;

    std::map<std::string, std::unique_ptr<Shader>> shaders;
    std::unique_ptr<Shader> uiShader;

    std::unique_ptr<Model> lobbyAsset;
    std::unique_ptr<Model> finalDoorAsset; // Left door of the final door

    std::unique_ptr<Model> hotelRoomStraightX; // Doors face +X and -X directions
    std::unique_ptr<Model> hotelRoomStraightZ; // Doors face +Z and -Z directions

    std::unique_ptr<Model> hotelRoomBendPosXPosZ; // Doors face +X and +Z directions
    std::unique_ptr<Model> hotelRoomBendPosXNegZ; // Doors face +X and -Z directions
    std::unique_ptr<Model> hotelRoomBendNegXPosZ; // Doors face -X and +Z directions
    std::unique_ptr<Model> hotelRoomBendNegXNegZ; // Doors face -X and -Z directions

    std::unique_ptr<Model> hotelRoomTPosX; // Blocking wall faces +X
    std::unique_ptr<Model> hotelRoomTNegX; // Blocking wall faces -X

    std::unique_ptr<Model> hallwayX; // Hallway extending along the X axis
    std::unique_ptr<Model> hallwayZ; // Hallway extending along the Z axis

    std::unique_ptr<Model> tableAsset;
    std::unique_ptr<Model> doorAsset;
    std::unique_ptr<Model> keyAsset;

    std::unique_ptr<Model> swampRoomAsset;
    std::unique_ptr<Model> lilypadAsset;
    std::unique_ptr<Model> frogAsset;

    std::unique_ptr<Model> circusRoomAsset;

    std::unique_ptr<Model> pianoRoomAsset;

    std::unordered_map<std::string, std::unique_ptr<ModelInstance>>
        modelInstances; // Top-level model instances with their child models.

    std::unordered_map<int, Player> players; // Active players in the scene.

    FireflyRenderer fireflyRenderer;
    std::vector<Firefly> fireflies;

    float lastFrame = 0.0f;
};
