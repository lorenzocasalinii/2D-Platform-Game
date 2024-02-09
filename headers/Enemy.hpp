#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.hpp"
#include <cstdlib>
#define MAX_ENEMY 10

class Enemy : public Character {
    private:
        bool canMove;
        bool moveRight;
        int movingX;
        int maxMovement;
        int movementCooldown;
        int movementCounter;
        bool canShoot;

    public: 
        Enemy();
        Enemy(int x, int y, char c, int hp, int d, int r, int sc, bool move, bool shoot);

        void drawEnemy(WINDOW * win);

        bool hasLineOfSight(WINDOW * win, int xP);
        void startShooting(int xP, int yP, pBullet &head, WINDOW * win);
        void move(WINDOW * win);

        bool getCanMove();
        bool getMoveRight();
        bool getCanShoot();

        void setCanMove(bool m);
        void setCanShoot(bool s);
        
        
};

struct enemyList {
    Enemy enemy;
    enemyList* nextEnemy = NULL;
    enemyList* previousEnemy = NULL;
};
typedef enemyList* pEnemy;

#endif