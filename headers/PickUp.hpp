#ifndef PICKUP_HPP
#define PICKUP_HPP

#include <ncurses.h>
#define MAX_PICKUP 5

class PickUp {
    private:
        int x;
        int y;
        char c;
        
    public:
        PickUp();
        PickUp(int x, int y, char c);

        void drawPickUp(WINDOW * win);

        void setX(int xPU);
        void setY(int yPU);
        void setC(char cPU);

        int getX();
        int getY();
        char getC();
};

struct pickUpList {
    PickUp pickUp;
    pickUpList* nextPickUp = NULL;
    pickUpList* previousPickUp = NULL;
};
typedef pickUpList* pPickUp;

#endif