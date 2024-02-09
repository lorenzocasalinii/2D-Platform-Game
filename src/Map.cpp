#include "Map.hpp"

// CONSTRUCTOR
Map::Map() {
    oldTemplate = 0;                        
    latestTemplate = -1;                  
    numOfGeneratedLevels = 0;           
    numOfCurrentLevel = 0;              
    numEnemies = 5;                     
    numPickUps = 4;                     
    incrH = 0;                          
    incrD = 0;                          
}

// Choose a random template
void Map::pickRandomLevel() {
    oldTemplate = latestTemplate;
    srand(time(0));
    while(latestTemplate == oldTemplate) {
        latestTemplate = rand() % 8;
    }
}


// Create a new level and add it to the list
void Map::createNewLevel(pLevel &currentLevel) {
    Platform currentPlatforms[MAX_PLAT];       
    Door currentDoors[NUM_DOOR];                
    pEnemy currentEnemies = NULL;  
    pPickUp currentPickUps = NULL;             
    pickRandomLevel();
    loadNewLevel(currentPlatforms, currentDoors, currentEnemies, currentPickUps);
    addLevel(currentLevel, currentPlatforms, currentDoors, currentEnemies, currentPickUps);
}

// HELPER FUNCTIONS TO COPY VALUES
void Map::copyPlatform(Platform &toLoad, int x, int y, int l, char c) {
    toLoad.setX(x);
    toLoad.setY(y);
    toLoad.setL(l);
    toLoad.setC(c);
}

void Map::copyDoor(Door &toLoad, int x, int y, int l, bool r, char c) {
    toLoad.setX(x);
    toLoad.setY(y);
    toLoad.setL(l);
    toLoad.setR(r);
    toLoad.setC(c);
}

Enemy Map::copyEnemy(Enemy toCopy) {
    Enemy toLoad(toCopy.getX(), toCopy.getY(), toCopy.getC(), toCopy.getHealth(), toCopy.getDamage(), toCopy.getRange(), toCopy.getShootingCooldown(), toCopy.getCanMove(), toCopy.getCanShoot());
    return toLoad;
}

PickUp Map::copyPickUp(PickUp toCopy) {
    PickUp toLoad(toCopy.getX(), toCopy.getY(), toCopy.getC());
    return toLoad;
}


// Load a new level using default values
void Map::loadNewLevel(Platform p[], Door d[], pEnemy &newEnemies, pPickUp &newPickUps) {
    MapDefaultValues mapval;
    switch(latestTemplate) {
        case 0:
            for(int i = 0; i < MAX_PLAT; i++) {
                copyPlatform(p[i], mapval.platX0[i], mapval.platY0[i], mapval.platL0[i], mapval.platC0[i]);
            }
            for(int i = 0; i < NUM_DOOR; i++) {
                copyDoor(d[i], mapval.door0[i].getX(), mapval.door0[i].getY(), mapval.door0[i].getL(), mapval.door0[i].getR(), mapval.door0[i].getC());
            }
            for(int i = 0; i < numEnemies; i++) { 
                Enemy e(mapval.enemyX0[i], mapval.enemyY0[i], mapval.enemyC0[i], mapval.enemyHP0[i] + incrH, mapval.enemyD0[i] + incrD, mapval.enemyR0[i], mapval.enemySC0[i], mapval.enemyCM0[i], mapval.enemyCS0[i]);
                addEnemy(newEnemies, e); 
            }
            for(int i = 0; i < numPickUps; i++){
                PickUp pu(mapval.pickUpX0[i], mapval.pickUpY0[i], mapval.pickUpC0[i]);
                addPickUp(newPickUps, pu);
            }
            break;
        case 1:
            for(int i = 0; i < MAX_PLAT; i++) {
                copyPlatform(p[i], mapval.platX1[i], mapval.platY1[i], mapval.platL1[i], mapval.platC1[i]);
            }
            for(int i = 0; i < NUM_DOOR; i++) {
                copyDoor(d[i], mapval.door1[i].getX(), mapval.door1[i].getY(), mapval.door1[i].getL(), mapval.door1[i].getR(), mapval.door1[i].getC());
            }
            for(int i = 0; i < numEnemies; i++) {
                Enemy e(mapval.enemyX1[i], mapval.enemyY1[i], mapval.enemyC1[i], mapval.enemyHP1[i] + incrH, mapval.enemyD1[i] + incrD, mapval.enemyR1[i], mapval.enemySC1[i], mapval.enemyCM1[i], mapval.enemyCS1[i]);
                addEnemy(newEnemies, e); 
            }
            for(int i = 0; i < numPickUps; i++){
                PickUp pu(mapval.pickUpX1[i], mapval.pickUpY1[i], mapval.pickUpC1[i]);
                addPickUp(newPickUps, pu);
            }
            break;
        case 2:
            for(int i = 0; i < MAX_PLAT; i++) {
                copyPlatform(p[i], mapval.platX2[i], mapval.platY2[i], mapval.platL2[i], mapval.platC2[i]);
            }
            for(int i = 0; i < NUM_DOOR; i++) {
                copyDoor(d[i], mapval.door2[i].getX(), mapval.door2[i].getY(), mapval.door2[i].getL(), mapval.door2[i].getR(), mapval.door2[i].getC());
            }
            for(int i = 0; i < numEnemies; i++) {
                Enemy e(mapval.enemyX2[i], mapval.enemyY2[i], mapval.enemyC2[i], mapval.enemyHP2[i] + incrH, mapval.enemyD2[i] + incrD, mapval.enemyR2[i], mapval.enemySC2[i], mapval.enemyCM2[i], mapval.enemyCS2[i]);
                addEnemy(newEnemies, e); 
            }
            for(int i = 0; i < numPickUps; i++){
                PickUp pu(mapval.pickUpX2[i], mapval.pickUpY2[i], mapval.pickUpC2[i]);
                addPickUp(newPickUps, pu);
            }
            break;
        case 3:
            for(int i = 0; i < MAX_PLAT; i++) {
                copyPlatform(p[i], mapval.platX3[i], mapval.platY3[i], mapval.platL3[i], mapval.platC3[i]);
            }
            for(int i = 0; i < NUM_DOOR; i++) {
                copyDoor(d[i], mapval.door3[i].getX(), mapval.door3[i].getY(), mapval.door3[i].getL(), mapval.door3[i].getR(), mapval.door3[i].getC());
            }
            for(int i = 0; i < numEnemies; i++) {
                Enemy e(mapval.enemyX3[i], mapval.enemyY3[i], mapval.enemyC3[i], mapval.enemyHP3[i] + incrH, mapval.enemyD3[i] + incrD, mapval.enemyR3[i], mapval.enemySC3[i], mapval.enemyCM3[i], mapval.enemyCS3[i]);
                addEnemy(newEnemies, e); 
            }
            for(int i = 0; i < numPickUps; i++){
                PickUp pu(mapval.pickUpX3[i], mapval.pickUpY3[i], mapval.pickUpC3[i]);
                addPickUp(newPickUps, pu);
            }
            break;
        case 4:
            for(int i = 0; i < MAX_PLAT; i++) {
                copyPlatform(p[i], mapval.platX4[i], mapval.platY4[i], mapval.platL4[i], mapval.platC4[i]);
            }
            for(int i = 0; i < NUM_DOOR; i++) {
                copyDoor(d[i], mapval.door4[i].getX(), mapval.door4[i].getY(), mapval.door4[i].getL(), mapval.door4[i].getR(), mapval.door4[i].getC());
            }
            for(int i = 0; i < numEnemies; i++) {
                Enemy e(mapval.enemyX4[i], mapval.enemyY4[i], mapval.enemyC4[i], mapval.enemyHP4[i] + incrH , mapval.enemyD4[i] + incrD, mapval.enemyR4[i], mapval.enemySC4[i], mapval.enemyCM4[i], mapval.enemyCS4[i]);
                addEnemy(newEnemies, e); 
            }
            for(int i = 0; i< numPickUps; i++){
                PickUp pu(mapval.pickUpX4[i], mapval.pickUpY4[i], mapval.pickUpC4[i]);
                addPickUp(newPickUps, pu);
            }
            break;
        case 5:
            for(int i = 0; i < MAX_PLAT; i++) {
                copyPlatform(p[i], mapval.platX5[i], mapval.platY5[i], mapval.platL5[i], mapval.platC5[i]);
            }
            for(int i = 0; i < NUM_DOOR; i++) {
                copyDoor(d[i], mapval.door5[i].getX(), mapval.door5[i].getY(), mapval.door5[i].getL(), mapval.door5[i].getR(), mapval.door5[i].getC());
            }
            for(int i = 0; i < numEnemies; i++) {
                Enemy e(mapval.enemyX5[i], mapval.enemyY5[i], mapval.enemyC5[i], mapval.enemyHP5[i] + incrH, mapval.enemyD5[i] + incrD, mapval.enemyR5[i], mapval.enemySC5[i], mapval.enemyCM5[i], mapval.enemyCS5[i]);
                addEnemy(newEnemies, e); 
            }
            for(int i = 0; i < numPickUps; i++){
                PickUp pu(mapval.pickUpX5[i], mapval.pickUpY5[i], mapval.pickUpC5[i]);
                addPickUp(newPickUps, pu);
            }
            break;
        case 6:
            for(int i = 0; i < MAX_PLAT; i++) {
                copyPlatform(p[i], mapval.platX6[i], mapval.platY6[i], mapval.platL6[i], mapval.platC6[i]);
            }
            for(int i = 0; i < NUM_DOOR; i++) {
                copyDoor(d[i], mapval.door6[i].getX(), mapval.door6[i].getY(), mapval.door6[i].getL(), mapval.door6[i].getR(), mapval.door6[i].getC());
            }
            for(int i = 0; i < numEnemies; i++) {
                Enemy e(mapval.enemyX6[i], mapval.enemyY6[i], mapval.enemyC6[i], mapval.enemyHP6[i] + incrH, mapval.enemyD6[i] + incrD , mapval.enemyR6[i], mapval.enemySC6[i], mapval.enemyCM6[i], mapval.enemyCS6[i]);
                addEnemy(newEnemies, e); 
            }
            for(int i = 0; i < numPickUps; i++){
                PickUp pu(mapval.pickUpX6[i], mapval.pickUpY6[i], mapval.pickUpC6[i]);
                addPickUp(newPickUps, pu);
            }
            break;
        case 7:
            for(int i = 0; i < MAX_PLAT; i++) {
                copyPlatform(p[i], mapval.platX7[i], mapval.platY7[i], mapval.platL7[i], mapval.platC7[i]);
            }
            for(int i = 0; i < NUM_DOOR; i++) {
                copyDoor(d[i], mapval.door7[i].getX(), mapval.door7[i].getY(), mapval.door7[i].getL(), mapval.door7[i].getR(), mapval.door7[i].getC());
            }
            for(int i = 0; i < numEnemies; i++) {
                Enemy e(mapval.enemyX7[i], mapval.enemyY7[i], mapval.enemyC7[i], mapval.enemyHP7[i] + incrH , mapval.enemyD7[i] + incrD, mapval.enemyR7[i], mapval.enemySC7[i], mapval.enemyCM7[i], mapval.enemyCS7[i]);
                addEnemy(newEnemies, e); 
            }
            for(int i = 0; i < numPickUps; i++){
                PickUp pu(mapval.pickUpX7[i], mapval.pickUpY7[i], mapval.pickUpC7[i]);
                addPickUp(newPickUps, pu);
            }
            break;
        default:
            break;
    }
}


// Perform tailInsert of a new level
void Map::addLevel(pLevel &LAST, Platform p[], Door d[], pEnemy e, pPickUp pu) {
    pLevel newLevel = new Level;
    
    for(int i = 0; i < MAX_PLAT && p[i].getX() != 0; i++) {
        copyPlatform(newLevel->levelPlatforms[i], p[i].getX(), p[i].getY(), p[i].getL(), p[i].getC());
        newLevel->numPlats++;
    }
    for(int i = 0; i < NUM_DOOR; i++) {
        copyDoor(newLevel->levelDoors[i], d[i].getX(), d[i].getY(), d[i].getL(), d[i].getR(), d[i].getC());
    }
    while(e != NULL) {
        addEnemy(newLevel->levelEnemies, e->enemy);
        newLevel->aliveEnemies++;
        e = e->nextEnemy;
    }
    while(pu != NULL) {
        addPickUp(newLevel->levelPickUps, pu->pickUp);
        newLevel->activePickUps++;
        pu = pu->nextPickUp;
    }

    newLevel->nextLevel = NULL;
    newLevel->previousLevel = LAST;
    newLevel->levelTemplate = latestTemplate;
    if(LAST != NULL) {
        LAST->nextLevel = newLevel;
    }
    LAST = newLevel;
}

// Perform headInsert of a new enemy
void Map::addEnemy(pEnemy &head, Enemy e) {
    pEnemy newEnemy = new enemyList;
    newEnemy->enemy = copyEnemy(e);
    newEnemy->nextEnemy = head;
    newEnemy->previousEnemy = NULL;
    if(head != NULL) {
        head->previousEnemy = newEnemy;
    }
    head = newEnemy;
}

// Perform headInsert of a new pickup
void Map::addPickUp(pPickUp &head, PickUp pu) {
    pPickUp newPickUp = new pickUpList;
    newPickUp->pickUp = copyPickUp(pu);
    newPickUp->nextPickUp = head;
    newPickUp->previousPickUp = NULL;
    if(head != NULL) {
        head->previousPickUp = newPickUp;
    }
    head = newPickUp;
}


// Print the map
void Map::printMap(WINDOW * win, pLevel currentLevel) {
    for(int i = 0; i < currentLevel->numPlats; i++) {
        currentLevel->levelPlatforms[i].printPlatform(win);
    }
    for(int i = 0; i < NUM_DOOR; i++) {
        currentLevel->levelDoors[i].printDoor(win);
    }
    printEnemies(win, currentLevel->levelEnemies);
    printPickUps(win, currentLevel->levelPickUps);
}

// Print all active enemies
void Map::printEnemies(WINDOW * win, pEnemy e) {
    pEnemy temp = e;
    while(temp != NULL) {
        temp->enemy.drawEnemy(win);
        temp = temp->nextEnemy;
    }
}

// Print the pickups
void Map::printPickUps(WINDOW * win, pPickUp pu) {
    pPickUp temp = pu;
    while(temp != NULL) {
        temp->pickUp.drawPickUp(win);
        temp = temp->nextPickUp;
    }
}


void Map::resetBulletLists(pBullet &player, pBullet &enemy) {
    emptyBulletList(player);
    emptyBulletList(enemy);
}

// 
void Map::emptyBulletList(pBullet &head) {
    while(head != NULL) {
        pBullet temp = head;
        head = head->nextBullet;
        delete temp;
    }
}

// Delete all active enemies
void Map::deleteEnemies(WINDOW * win, pEnemy e) {
    pEnemy temp = e;
    while(temp != NULL) {
        if(temp->enemy.getCanMove()) {
            temp->enemy.deleteCharacter(win);
        }
        temp = temp->nextEnemy;
    }
}

// Increase the difficulty
void Map::increaseDifficulty(){
    numEnemies++;
    if(numEnemies > MAX_ENEMY) {
        numEnemies = MAX_ENEMY;
    }
    incrH += 5;
    incrD += 5;
    if(numOfGeneratedLevels % 6 == 0) {
        numPickUps--;
    } 
}

// Increase the difficulty depending on the current powerups
void Map::increaseDifficultyPowerup(PowerUp powerup) {
    int cont = 0;
    for(int i = 0; i < MAX_BONUS; i++) {
        if(powerup.bonus[i].OwnedQuantity > 0) {
            cont += powerup.bonus[i].OwnedQuantity;
        }
        else if(powerup.bonus[i].IsActive) {
            cont++;
        }
    }
    numEnemies += cont;
    if(numEnemies > MAX_ENEMY) {
        numEnemies = MAX_ENEMY;
    }
    incrH += cont * 5;
    incrD += cont * 5;
    if(cont >= 3 && cont <= 6) {
        numPickUps--;
    }
    if(cont >= 7) {
        numPickUps -= 2;
    }
    if(numPickUps < 1) {
        numPickUps = 1;
    }
}

// GETTERS
int Map::getLatestTemplate() {
    return latestTemplate;
}

int Map::getOldTemplate() {
    return oldTemplate;
}

int Map::getNumOfGeneratedLevels() {
    return numOfGeneratedLevels;
}

int Map::getNumOfCurrentLevel() {
    return numOfCurrentLevel;
}

// SETTERS
void Map::setLatestTemplate(int p) {
    latestTemplate = p;
}

void Map::setOldTemplate(int p) {
    oldTemplate = p;
}

void Map::setNumOfGeneratedLevels(int s) {
    numOfGeneratedLevels += s;
}

void Map::setNumOfCurrentLevel(int s) {
    numOfCurrentLevel += s;
}