#pragma once

#include <player.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <unordered_map>
#include "camera.hpp"
#include "config.hpp"
#include "cube.hpp"
#include "model.hpp"
#include "shader.hpp"

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
     */
    Scene();

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
     * @brief Renders the entire scene.
     * 
     * Draws static models and dynamic player cubes.
     * 
     * @param camera The active camera providing view and projection matrices.
     */
    void render(const Camera& camera);

private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> modelShader;

    std::unique_ptr<Model> room;
    std::unique_ptr<Model> table;

    std::unordered_map<int, Player> players;    // Active players in the scene.
};
