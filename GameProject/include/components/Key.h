#pragma once
#include "Interactable.h"

class Key: public Interactable
{
public:
    Key(int ID);
    ~Key();
    void interact();

private:
    int keyID;
};