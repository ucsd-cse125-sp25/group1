#include "components/interactable.hpp"

Interactable::Interactable() = default;

void Interactable::interact(int playerID) {
  // TODO: handle keypress
  sendInteractRequest(playerID);
}