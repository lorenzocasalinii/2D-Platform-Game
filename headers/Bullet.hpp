#ifndef BULLET_HPP
#define BULLET_HPP

#include<ncurses.h>

class Bullet{

    private:
        int xB, yB;
        int startingX;
        int deletingX;
        int maxRange;
        bool direction;         // true = destra, false = sinistra
        int damage;
        char bulletChar;

    public:
        Bullet();
        Bullet(int x, int y, bool direction, int damage, int range);
        
        void printBullet(WINDOW * win);
        void deleteBullet(WINDOW * win);
        
        int getXB();
        int getYB();
        int getStartingX();
        int getMaxRange();
        bool getDirection();
        int getDamage();
        
        void setXB(int x);
        void setBulletChar(char c);
        void setDeletingX(int x);
};

struct bulletList {
    Bullet b;
    bulletList* nextBullet = NULL;
};
typedef bulletList* pBullet;

#endif