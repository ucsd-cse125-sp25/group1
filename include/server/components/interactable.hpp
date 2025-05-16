#pragma once
#include "player.hpp"
#include "components/object.hpp"

class Player;
class Object;

class Interactable : public Object
{
public:
    Interactable(int id, const glm::vec3& position, const glm::vec3& direction, float width, float height);
    virtual ~Interactable() = default;
    void interact(const Player &player); //calls the overriden handleInteract function.

protected:
    virtual void handleInteract(const Player &player) = 0; //Pure virtual function, must be implemented by derived classes

private:
    int objectID;
    RigidBody body;
};