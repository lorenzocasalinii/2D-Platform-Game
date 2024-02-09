#include "BulletHelper.hpp"

// Print all the player bullets
void BulletHelper::printPlayerBullets(pBullet &head, WINDOW * win, Player &p, pLevel currentLevel, int xMax, PowerUp powerup) {
    pBullet temp = head;
    while(temp != NULL) {
        if(abs(temp->b.getXB() - temp->b.getStartingX()) < temp->b.getMaxRange()) {
            if(!checkMap(win, temp->b, xMax) && !detectEnemyCollision(win, currentLevel->levelEnemies, temp->b, p, currentLevel->aliveEnemies)) {
                if(powerup.bonus[1].IsActive) {
                    init_pair(3, COLOR_RED, COLOR_BLACK); 
                    wattron(win, COLOR_PAIR(3));
                }
                temp->b.printBullet(win);
                wattroff(win, COLOR_PAIR(3));
                temp->b.getDirection() ? temp->b.setXB(temp->b.getXB() + 1) : temp->b.setXB(temp->b.getXB() - 1);
            }
            else {
                head = removeBullet(head, temp);
            }
        }
        else {
            head = removeBullet(head, temp);
        }
        temp = temp->nextBullet;
    }
}

// Print all the enemy bullets
void BulletHelper::printEnemyBullets(pBullet &head, WINDOW * win, Player &p, int xMax, PowerUp powerup) {
    pBullet temp = head;
    while(temp != NULL) {  
        if(abs(temp->b.getXB() - temp->b.getStartingX()) < temp->b.getMaxRange()) {
            if(!checkMap(win, temp->b, xMax) && !detectCharacterCollision(win, temp->b, p, powerup)) {
                temp->b.printBullet(win);
                temp->b.getDirection() ? temp->b.setXB(temp->b.getXB() + 1) : temp->b.setXB(temp->b.getXB() - 1);
            }
            else {
                head = removeBullet(head, temp);
            }
        }
        else {
            head = removeBullet(head, temp);
        }
        temp = temp->nextBullet;
    }
}

// Check bullet collisions with walls, platforms and doors
bool BulletHelper::checkMap(WINDOW * win, Bullet b, int xMax) {  
    if(b.getDirection() && b.getXB() == xMax) {
        return true;
    }
    if(!b.getDirection() && b.getXB() == 0) {
        return true;
    }
    int xB = b.getXB();
    int yB = b.getYB();
    char nextpos = mvwinch(win, yB, xB);
    if(nextpos == '=' || nextpos == '|' || nextpos == '[' || nextpos == ']') {
        return true;
    }
    return false; 
}

// Handle collisions with bullets shot by the player
bool BulletHelper::detectEnemyCollision(WINDOW * win, pEnemy &e, Bullet b, Player &p, int &aliveEnemies) {
    bool collision = false;
    pEnemy temp = e;
    while(temp != NULL && !collision){
        if(temp->enemy.getY() == b.getYB()) {
            if(temp->enemy.getX() - 1 == b.getXB() || temp->enemy.getX() == b.getXB() || temp->enemy.getX() + 1 == b.getXB()) {                   
                temp->enemy.setHealth(-b.getDamage());
                if(!temp->enemy.getIsAlive()) {
                    temp->enemy.deleteCharacter(win);
                    wrefresh(win);  
                    e = removeEnemy(e, temp->enemy);
                    aliveEnemies--;
                    p.setEnemiesKilled(1);
                    p.setPoints(10);
                }
                collision = true;
            }
        }
        temp = temp->nextEnemy;
    }
    return collision;
}

// Handle collisions with bullets shot by the enemies
bool BulletHelper::detectCharacterCollision(WINDOW * win, Bullet b, Player &p, PowerUp powerup) {
    if(b.getYB() == p.getY()) {
        if(p.getX() == b.getXB() || p.getX() - 1 == b.getXB() || p.getX() + 1 == b.getXB()) {
            if(!powerup.bonus[2].IsActive){
                p.setHealth(-b.getDamage());
            }
            p.setCharacterHits(1);
            return true;
        }
    }
    char checkForEnemyChar = mvwinch(win, b.getYB(), b.getXB());
    char checkForEnemyCharNext = mvwinch(win, b.getYB(), b.getDirection() ? b.getXB() + 1 : b.getXB() - 1);
    if(checkForEnemyChar == '#' || checkForEnemyChar == 'O' || checkForEnemyCharNext == '#' || checkForEnemyCharNext == 'O') {
        return true;
    }
    return false;
}


// Remove bullet from a list
pBullet BulletHelper::removeBullet(pBullet head, pBullet bullet) {
    if(head == NULL) {
        return NULL;
    }
    if(head == bullet) {
        pBullet newHead = head->nextBullet;
        delete bullet;
        return newHead;
    }
    pBullet current = head;
    pBullet previous = NULL;
    while(current != NULL && current != bullet) {
        previous = current;
        current = current->nextBullet;
    }
    previous->nextBullet = current->nextBullet;
    delete current;
    return head;
}

// Remove enemy from a list
pEnemy BulletHelper::removeEnemy(pEnemy e, Enemy toRemove) {
    pEnemy temp = e;
    bool leave = false;
        while(temp != NULL && !leave) {
            if((temp->enemy.getX() == toRemove.getX()) && (temp->enemy.getY() == toRemove.getY()) && !temp->enemy.getIsAlive()) {
                if(temp->previousEnemy != NULL) {
                    temp->previousEnemy->nextEnemy = temp->nextEnemy;
                } 
                else {
                    e = temp->nextEnemy;
                }
                if(temp->nextEnemy != NULL) {
                    temp->nextEnemy->previousEnemy = temp->previousEnemy;
                }
                delete temp;
                leave = true;
            }
            temp = temp->nextEnemy;
        }
    return e;
}

// Delete all bullets from the screen
void BulletHelper::deleteBullets(pBullet head, WINDOW * win) {
    while(head != NULL) {
        head->b.deleteBullet(win);
        head->b.setDeletingX(head->b.getXB());
        head = head->nextBullet;
    }
}