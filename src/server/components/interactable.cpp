#include "components/interactable.hpp"

Interactable::Interactable() = default;

void Interactable::interact(const Player &player){
    handleInteract(player);
}