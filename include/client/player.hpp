#pragma once

#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <set>
#include <string>
#include "animatedModel.hpp"
#include "animation.hpp"
#include "animator.hpp"
#include "config.hpp"
#include "cube.hpp"
#include "shader.hpp"

/**
 * @brief Represents the player
 *
 * Stores player-specific data like position, direction, visual representation, along with
 * keys and current room ID.
 * Currently, each player is drawn as a colored cube aligned with their facing direction.
 */
class Player {
  public:
    /**
     * @brief Constructs a Player instance.
     *
     * Initializes the player ID, position, direction, and creates a cube for the character.
     *
     * @param id Player ID.
     * @param position Initial position.
     * @param direction Initial facing direction.
     */
    Player(int id, const glm::vec3& position, const glm::vec3& direction);

    ~Player() = default;

    // Move semantics: allow efficient transfer of resources (the player cube)
    // when inserting into containers (e.g., std::unordered_map).
    Player(Player&&) noexcept = default;
    Player& operator=(Player&&) noexcept = default;

    /**
     * @brief Initializes all components required for the animated character.
     */
    void init();

    /**
     * @brief Updates the current animation time.
     *
     * @param deltaTime Time since the last frame.
     */
    void updateTime(float deltaTime) {
        animators[state]->update(deltaTime);
    }

    /**
     * @brief Draws the player.
     *
     * Applies translation and rotation based on position and facing direction,
     * sets shader uniforms, and draws the character cube.
     *
     * @param shader Shader program to use for rendering.
     * @param boundingBoxMode If true, draws bounding boxes for debugging.
     */
    void draw(Shader& shader);

    /**
     * @brief Gets the player's current position.
     *
     * @return const glm::vec3& Reference to the position vector.
     */
    inline const glm::vec3& getPosition() const {
        return position;
    }

    /**
     * @brief Sets the player's world position.
     *
     * Updates the player's position in world space.
     *
     * @param newPosition The new position vector.
     */
    inline void setPosition(const glm::vec3& newPosition) {
        position = newPosition;
    }

    /**
     * @brief Gets the player's current facing direction.
     *
     * @return const glm::vec3& Reference to the direction vector.
     */
    inline const glm::vec3& getDirection() const {
        return direction;
    }

    /**
     * @brief Sets the player's facing direction.
     *
     * Updates the direction the player is facing.
     *
     * @param newDirection The new direction vector.
     */
    inline void setDirection(const glm::vec3& newDirection) {
        direction = newDirection;
    }

    /**
     * @brief Returns the set of key IDs the player possesses.
     *
     * @return std::set<int> A copy of the player's key ID list.
     */
    const std::set<int>& getKeyIDs() const {
        return keyIDs;
    }

    /**
     * @brief Adds a key to the player's inventory.
     *
     * @param keyID ID of the key to add.
     */
    void addKey(int keyID) {
        keyIDs.insert(keyID);
    }

    /**
     * @brief Removes a key from the player's inventory.
     *
     * Searches for the given key ID and removes it if found.
     *
     * @param keyID ID of the key to remove.
     * @return true if the key was found and removed; false otherwise.
     */
    bool removeKey(int keyID) {
        bool found = keyIDs.erase(keyID) > 0;
        return found;
    }

    /**
     * @brief Gets the ID of the room the player is currently in.
     *
     * @return int The current room ID.
     */
    int getCurrRoomID() const {
        return currRoomID;
    }

    /**
     * @brief Sets the current room ID for the player.
     *
     * @param id New room ID to set.
     */
    void setCurrRoomID(int roomID) {
        currRoomID = roomID;
    }

    /**
     * @brief Gets the player's name.
     *
     * Returns a const reference to the player's current name.
     *
     * @return const std::string& Read-only reference to the name.
     */
    const std::string& getName() const {
        return name;
    }

    /**
     * @brief Sets the player's name.
     *
     * @param playerName The new name for the player.
     */
    void setName(const std::string& playerName) {
        name = playerName;
    }

    /**
     * @brief Sets player's animation state.
     *
     * @param state 0: idle, 1: run
     */
    void setState(int state) {
        this->state = state;
    }

    /**
     * @brief Gets player's animation state.
     *
     * @return 0: idle, 1: run
     */
    int getState() const {
        return state;
    }

  private:
    int id;              // Player ID.
    glm::vec3 position;  // Current position of the player.
    glm::vec3 direction; // Current facing direction of the player.

    int characterID;

    std::array<std::unique_ptr<Animator>, 2> animators;
    std::array<std::unique_ptr<Animation>, 2> animations;
    std::array<std::unique_ptr<AnimatedModel>, 2> characters;
    int state = 0;

    int currRoomID = 0;    // Room the player is currently in
    std::string name = ""; // Name chosen by the player
    std::set<int> keyIDs;  // Keys (by ID) the player has collected
};
