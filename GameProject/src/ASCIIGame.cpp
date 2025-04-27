// game.cpp
#include <iostream>
#include <vector>
#include "../include/components/Player.h"
#include "../include/components/Room.h"
#include "../include/components/Door.h"
#include "../include/components/Key.h"

int main() {
    const int W = 40, H = 20;
    std::vector<Room> rooms;
    std::vector<Door> doors;
    std::vector<Key> keys;

    // 1. Create a room and a door
    rooms.emplace_back(1, Coord{2,2,0}, 12, 8);
    rooms.emplace_back(2, Coord{14,2,0}, 12, 8);
    doors.emplace_back(12, 1, 2, 12, Coord{13,6,0});     // door on left wall
    keys.emplace_back(12, Coord{3,3,0});

    // 2. Place player inside
    Player p("Hero", Coord{4,4,0});

    bool running = true;
    while (running) {
        // Prepare blank grid
        std::vector<std::vector<char>> map(H, std::vector<char>(W,' '));
        // Draw rooms & doors
        for (auto& r : rooms) r.draw(map);
        for (auto& d : doors) d.draw(map);
        for (auto& k : keys) k.draw(map);
        // Draw player
        p.draw(map);

        // Render
        std::system("clear");  // or "cls" on Windows
        for (auto& row : map) {
            for (char c: row) std::cout << c;
            std::cout << "\n";
        }

        // Input
        char cmd;
        std::cin >> cmd;
        int dx=0, dy=0;
        switch(cmd) {
          case 'w': dy=-1; break;
          case 's': dy=+1; break;
          case 'a': dx=-1; break;
          case 'd': dx=+1; break;
          case 'e': // try open door underfoot
            {
              
              Coord pos = p.getPosition();
              //If we are interacting with a door
              for (auto& d : doors) {
                if (d.isAt(pos.x,pos.y)) {

                  //Everything here should be in the interact() or handleInteract()
                  if (d.isLocked()) {
                    if (d.unlockDoor(p.getKeys())) {
                      std::cout<<"Door unlocked!";
                    }
                    else std::cout<<"*Can't open*";
                  }
                  else d.openDoor();
                  //------------------------------------------------------------
                  continue;
              }
            }
            for (auto& k : keys) {
              if (k.isAt(pos.x,pos.y)) {
                p.addKey(k.getID());
                keys.erase(keys.begin()); //Should change this later to remove by ID
                std::cout<<"Picked up key!";
              }
            }
            
          }
            continue;
          case 'q':
            running = false;
            continue;
        }
        // Move
        if (!p.move(dx, dy, map)) {
            std::cout<<"*Invalid Move";
        };
    }
    return 0;
}