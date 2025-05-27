#include "components/interactable.hpp"

Interactable::Interactable(int id) : Object(id) {}

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
