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
     * @brief Renders shadow maps for static geometry.
     */
    void renderStaticShadowPass();

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

    int playerID;

    std::unordered_map<std::string, std::vector<PointLight>> pointLights;
    std::unordered_map<std::string, std::vector<std::unique_ptr<ShadowMap>>> staticShadowMaps;

    std::map<std::string, std::unique_ptr<Shader>> shaders;
    std::unique_ptr<Shader> uiShader;

    std::unique_ptr<Model> hotelRoomAsset;
    std::unique_ptr<Model> tableAsset;
    std::unique_ptr<Model> doorAsset;

    std::unique_ptr<Model> swampRoomAsset;
    std::unique_ptr<Model> lilypadAsset;
    std::unique_ptr<Model> frogAsset;

    std::unique_ptr<Model> circusRoomAsset;

    std::unordered_map<std::string, std::unique_ptr<ModelInstance>>
        modelInstances; // Top-level model instances with their child models.

    std::unordered_map<int, Player> players; // Active players in the scene.
};
