#ifndef BULLET_HELPER_HPP
#define BULLET_HELPER_HPP

#include<ncurses.h>
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

class BulletHelper {
    public:
        void printPlayerBullets(pBullet &head, WINDOW * win, Player &p, pLevel currentLevel, int x, PowerUp powerup);
        void printEnemyBullets(pBullet &head, WINDOW * win, Player &p, int x, PowerUp powerup);
        
        void deleteBullets(pBullet head, WINDOW * win);

        bool checkMap(WINDOW * win, Bullet b, int xMax);
        bool detectEnemyCollision(WINDOW * win, pEnemy &e, Bullet b, Player &p, int &aliveEnemies);
        bool detectCharacterCollision(WINDOW * win, Bullet b, Player &p, PowerUp powerup);

        pBullet removeBullet(pBullet headList, pBullet toRemove);
        pEnemy removeEnemy(pEnemy e, Enemy toRemove);
};

#endif 