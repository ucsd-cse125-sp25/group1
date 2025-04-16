#include "components/Interactable.h"

Interactable::Interactable(bool unlocks, bool opens, bool closes, bool moves)
    : canUnlock(unlocks), canOpen(opens), canClose(closes), canMove(moves)
{
    // Todo: any other setup if necessary
}

// Todo: add other function definitions