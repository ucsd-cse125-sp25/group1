#pragma once
#include "components/Interactable.h"

class Door: public Interactable
{
public:
	bool isLocked();
    // Todo: add constructor and destructor
    // Todo: add a mapper to which room the door leads to
private:
	bool _isLocked;
};