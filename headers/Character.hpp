#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include<ncurses.h>
#include "Bullet.hpp"

class Character {

    protected:
        int health;
        int damage;
        int range;
        int shootingCooldown;
        int shootingCounter;
        int x, y, xMax, yMax;
        char c;
        bool isAlive;

    public: 
        Character();
        Character(int x, int y, char c, int hp, int d, int r, int sc);
        Character(int width, int height, char c);
                
        void shoot(pBullet &head, bool right);
        pBullet addBullet(pBullet head, Bullet b); 

        void deleteCharacter(WINDOW * win);

        int getX();
        int getY();
        char getC();
        bool getIsAlive();
        int getHealth();
        int getDamage();
        int getRange();
        int getShootingCooldown();
        int getShootingCounter();

        void setX(int x);
        void setY(int y);
        void setC(char c);
        void setIsAlive(bool alive);
        void setHealth(int hp);
        void initializeHealth();
        void setDamage(int d);
        void setRange(int r);
        void setShootingCooldown(int scl);
        void setShootingCounter(int sct);
};

#endif 
