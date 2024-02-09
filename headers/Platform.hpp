#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include<ncurses.h>
#define MAX_PLAT 200

class Platform {
    protected:
        int x;                      
        int y;                      
        int length;                 
        char c;

    public:
        Platform();
        Platform(int x, int y, int l, char c); 

        void printPlatform(WINDOW * win);

        int getX();
        int getY();
        int getL();
        char getC();

        void setX(int x);
        void setY(int y);
        void setL(int l);
        void setC(char c); 
};

#endif


 

