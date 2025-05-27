#pragma once
#include "components/interactable.hpp"

class Frog : public Interactable {
  public:
    Frog(int id);

    void handleInteract(const Player& player) override;
};
