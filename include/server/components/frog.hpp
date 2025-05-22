#pragma once
#include "components/interactable.hpp"

class Frog : public Interactable {
  public:
    Frog(int id, glm::vec3 position, glm::vec3 direction, float width, float height);

    void handleInteract(const Player& player) override;
};
