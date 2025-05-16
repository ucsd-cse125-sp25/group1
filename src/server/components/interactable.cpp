#include "components/interactable.hpp"

Interactable::Interactable(int id, const glm::vec3& position, const glm::vec3& direction, float width, float height)
    : Object(id, position, direction, width, height),
    objectID(id),
    body(
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        0.0f, // static body
        new Transform{ position, direction },
        new BoxCollider{
            AABB,
            glm::vec3(-width / 2, -height / 2, -width / 2),
            glm::vec3(width / 2, height / 2, width / 2)
        },
        this,
        true
    ) {
}

void Interactable::interact(const Player &player){
    handleInteract(player);
}