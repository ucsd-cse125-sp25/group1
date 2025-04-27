#include "../../include/components/Interactable.h"

//TODO: any setup that is necessary
Interactable::Interactable() = default;
//Interactable::~Interactable()  = default;

// Todo: add other function definitions
void Interactable::interact() {
    //TODO: handle the user interaction input and then call handleInteraction implemented by the derived class

    handleInteract();
}