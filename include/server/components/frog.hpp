#pragma once
#include "components/interactable.hpp"

class Swamp; // Forward declaration of Swamp class

class Frog : public Interactable {
  public:
    Frog(int id, Swamp* swampRef);

    void handleInteract(const Player& player) override;

  private:
    Swamp* swamp; // Pointer to the Swamp instance this frog belongs to
};
