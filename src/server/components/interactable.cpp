#include "components/interactable.hpp"

Interactable::Interactable(int id, const glm::vec3& position, const glm::vec3& direction,
                           float width, float height)
    : Object(id, position, direction, width, height) {}

Interactable::Interactable()
  : Interactable(
      /*id=*/      0,
      /*position=*/glm::vec3{0.0f,0.0f,0.0f},
      /*direction=*/glm::vec3{0.0f,0.0f,1.0f},
      /*width=*/   1.0f,
      /*height=*/  1.0f
    )
{}void Interactable::interact(const Player& player) {
    handleInteract(player);
}
