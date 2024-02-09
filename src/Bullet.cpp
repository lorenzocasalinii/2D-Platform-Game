#include "Bullet.hpp"

// CONSTRUCTORS
Bullet::Bullet() {}

Bullet::Bullet(int x, int y, bool right, int d, int range) {
    xB = x;
    startingX = x;
    deletingX = x;
    yB = y;
    direction = right;
    damage = d;
    maxRange = range;
    bulletChar = '-';
}


// Print single bullet
void Bullet::printBullet(WINDOW * win) {
    mvwaddch(win, yB, xB, bulletChar);
}

// Delete single bullet
void Bullet::deleteBullet(WINDOW * win) {
    mvwaddch(win, yB, deletingX, ' ');
}


// GETTERS
int Bullet::getXB() {
    return xB;
}

int Bullet::getYB() {
    return yB;
}

int Bullet::getStartingX() {
    return startingX;
}

int Bullet::getMaxRange() {
    return maxRange;
}

bool Bullet::getDirection() {
    return direction;
}

int Bullet::getDamage() {
    return damage;
}


// SETTERS
void Bullet::setXB(int x) {
    xB = x;
}

void Bullet::setBulletChar(char c){
    bulletChar = c;
}

void Bullet::setDeletingX(int x) {
    deletingX = x;
}



    
