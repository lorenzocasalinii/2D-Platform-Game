#ifndef DOOR_HPP
#define DOOR_HPP

#include "Platform.hpp"
#include <ncurses.h>
#define NUM_DOOR 2

class Door : public Platform {
    private:
        bool spawnRight;                 // Indica se spawnare a destra o a sinistra della porta

    public:
        Door();
        Door(int x, int y, int h, bool right, char c);

        void printDoor(WINDOW * win);

        bool getR();
        void setR(bool b);
};

#endif