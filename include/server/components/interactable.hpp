#pragma once
#include "components/object.hpp"
#include "player.hpp"

class Player;
class Object;

class Interactable : public Object {
  public:
    Interactable(int id, const glm::vec3& position, const glm::vec3& direction, float width,
                 float height);
    Interactable();
    virtual ~Interactable() = default;
    void interact(const Player& player); // calls the overriden handleInteract function.

  protected:
    virtual void handleInteract(
        const Player& player) = 0; // Pure virtual function, must be implemented by derived classes
};
