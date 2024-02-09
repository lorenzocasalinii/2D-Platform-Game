#include "Door.hpp"

// CONSTRUCTORS
Door::Door() {}

Door::Door(int x, int y, int h, bool right, char c) : Platform(x, y, h, c) {
    spawnRight = right;
}


// Print the door
void Door::printDoor(WINDOW * win) {
    for(int i = 0; i < length; i++) {
        mvwaddch(win, y - i, x, c);
    }
}


// GETTERS
bool Door::getR() {
    return spawnRight;
}


// SETTERS
void Door::setR(bool b) {
    spawnRight = b;
}