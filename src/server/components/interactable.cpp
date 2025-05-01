#include "components/interactable.hpp"

Interactable::Interactable()
{
    // Todo: any other setup if necessary
}

// Todo: add other function definitions
void Interactable::interact() {
    //TODO: handle the user interaction input and then call handleInteraction implemented by the derived class

    Interactable::handleInteract();
}

void Interactable::handleInteract() {
    // Default behavior (can be empty)
}