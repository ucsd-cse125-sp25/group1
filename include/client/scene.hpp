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

// /**
//  * @brief Represents a player in the scene.
//  * 
//  * Stores player-specific data like position, direction, and visual representation.
//  * Currently, each player is drawn as a colored cube aligned with their facing direction.
//  */
// struct Player {
//     int id;                             // Player ID.
//     glm::vec3 position;                 // Current position of the player.
//     glm::vec3 direction;                // Current facing direction of the player.

//     std::unique_ptr<Cube> character;    // Cube model representing the player.

//     /**
//      * @brief Constructs a Player instance.
//      * 
//      * Initializes the player ID, position, direction, and creates a cube for the character.
//      * 
//      * @param id Player ID.
//      * @param position Initial position.
//      * @param direction Initial facing direction.
//      */
//     Player(int id, const glm::vec3& position, const glm::vec3& direction)
//         : id(id),
//           position(position),
//           direction(direction),
//           character(std::make_unique<Cube>()) {}

//     /**
//      * @brief Draws the player.
//      * 
//      * Applies translation and rotation based on position and facing direction,
//      * sets shader uniforms, and draws the character cube.
//      * 
//      * @param shader Shader program to use for rendering.
//      */
//     void draw(Shader& shader) {
//         glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
//         glm::vec3 rotationAxis = glm::cross(forward, direction);

//         if (glm::length(rotationAxis) < 0.0001f) {
//             rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
//         }

//         float dot = glm::dot(forward, direction);
//         float angle = acos(glm::clamp(dot, -1.0f, 1.0f));

//         glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::normalize(rotationAxis));
//         glm::mat4 playerModel = glm::translate(glm::mat4(1.0f), position);
//         playerModel *= rotation;

//         shader.setMat4("model", playerModel);
//         shader.setVec3("color", config::PLAYER_COLORS[id]);
//         character->draw();
//     }
// };

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
