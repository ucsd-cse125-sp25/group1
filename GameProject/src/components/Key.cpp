#pragma once
#include "../../include/components/Key.h"

Key::Key(int ID)
    : Interactable(), keyID(ID)
{

}

Key::Key(int ID, Coord pos)
    : Interactable(), 
    keyID(ID), 
    position(pos)
{}

Key::~Key(){

}

int Key::getID() {
    return keyID;
}

/**
 * interact is called when we press 'e'
 * That means that it should check that the spot is a key, then pick it up
 * 
 */
// void Key::interact(){

// }

void Key::handleInteract() {
    // your existing interact() logic, or call interact()
}

bool Key::isAt(int x, int y) const {
    return position.x == x && position.y == y;
}

void Key::draw(std::vector<std::vector<char>>& grid) const {
    char c = '?';
    grid[position.y][position.x] = c;
}