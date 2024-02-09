#include "Enemy.hpp"

// CONSTRUCTORS
Enemy::Enemy() {}

Enemy::Enemy(int x, int y, char c, int hp, int d, int r, int sc, bool move, bool shoot) : Character(x, y, c, hp, d, r, sc) {
    canMove = move;
    moveRight = false;
    movingX = 0;
    maxMovement = 20;
    movementCooldown = 2;
    movementCounter = 0;
    canShoot = shoot;
}


// Print a single enemy
void Enemy::drawEnemy(WINDOW * win) {
    init_pair(3, COLOR_RED, COLOR_BLACK); 
    wattron(win, COLOR_PAIR(3));
    mvwaddch(win, y, x, c);
    wattroff(win, COLOR_PAIR(3));
}


// Check if the enemy has line of sight
bool Enemy::hasLineOfSight(WINDOW * win, int xP) {
    bool lineOfSight = true;
    int step = (x < xP) ? 1 : -1;
    for(int i = (x < xP ? x + 1 : x - 1); (x < xP ? i < xP : i > xP) && lineOfSight; i += step) {
        char obstacle = mvwinch(win, y, i);
        if(obstacle == '=' || obstacle == '|') {
            lineOfSight = false;
        }
    }
    return lineOfSight;
}

// Handle enemy shooting
void Enemy::startShooting(int xP, int yP, pBullet &head, WINDOW * win) {
    if(shootingCounter > shootingCooldown && canShoot) {
        if(y == yP) {            
            if(xP > x) {
                if(x + range >= xP && hasLineOfSight(win, xP)) {
                    shoot(head, true);
                }
            }
            else if(xP < x) {
                if(x - range <= xP && hasLineOfSight(win, xP)) {
                    shoot(head, false);
                }
            }
        }     
    }
    else {
        shootingCounter++;
    }
}

// Handle enemy movement
void Enemy::move(WINDOW * win) {
    if(movementCounter > movementCooldown && canMove && shootingCounter != 0) {
        if(moveRight) {
            char d = mvwinch(win, y + 1, x + 1);
            char r = mvwinch(win, y, x + 1);
            if(movingX < maxMovement && (d == '=' || y == 22) && r == ' ') {
                x += 1;
                movingX++;
            }
            else {
                moveRight = false;
                movingX = 0;
            }
        }
        else {
            char d = mvwinch(win, y + 1, x - 1);
            char l = mvwinch(win, y, x - 1);
            if(movingX < maxMovement && (d == '=' || y == 22) && l == ' ') {
                x -= 1;
                movingX++;
            }
            else {
                moveRight = true;
                movingX = 0;
            }
        }
        movementCounter = 0;
    }
    else {
        movementCounter++;
    }
}



// GETTERS
bool Enemy::getCanMove() {
    return canMove;
}

bool Enemy::getMoveRight() {
    return moveRight;
}

bool Enemy::getCanShoot() {
    return canShoot;
}


// SETTERS
void Enemy::setCanMove(bool m) {
    canMove = m;
}

void Enemy::setCanShoot(bool s) {
    canShoot= s;
}