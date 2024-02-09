#include "Save.hpp"

// Save the current game info into a savefile
void Save::saveGame(Player p, Map m, pLevel l, PowerUp powerup) {
    ofstream outputFile;
    outputFile.open("savefile.txt", ios::trunc);  
    
    // Player info
    outputFile << 
        p.getX() << " " <<
        p.getY() << " " <<
        p.getHealth() << " " << 
        p.getDamage() << " " << 
        p.getRange() << " " << 
        p.getShootingCooldown() << " " <<  
        p.getPoints() << " " <<
        powerup.getCoins() << " " <<
        p.getEnemiesKilled() << " " << 
        p.getCharacterHits() << " " <<
        p.getTotalBullets() << " " <<
        p.getC() << "\n\n";
    
    // Map info
    outputFile << 
        m.getNumOfGeneratedLevels() << " " <<
        m.getNumOfCurrentLevel() << " " <<
        m.getLatestTemplate() << "\n\n";
    
    // Level info
    while(l != NULL) {
        outputFile << l->numPlats << "\n";

        for(int i = 0; i < l->numPlats; i++) {
            outputFile <<
                l->levelPlatforms[i].getX() << " " <<
                l->levelPlatforms[i].getY() << " " <<
                l->levelPlatforms[i].getL() << " " <<
                l->levelPlatforms[i].getC() << " ";
        }
        outputFile << "\n";

        for(int i = 0; i < NUM_DOOR; i++) {
            outputFile <<
                l->levelDoors[i].getX() << " " <<
                l->levelDoors[i].getY() << " " <<
                l->levelDoors[i].getL() << " " <<
                l->levelDoors[i].getR() << " " <<
                l->levelDoors[i].getC() << " ";
        }
        outputFile << "\n";


        outputFile << l->aliveEnemies << "\n";

        while(l->levelEnemies != NULL) {
            outputFile <<
                l->levelEnemies->enemy.getX() << " " <<
                l->levelEnemies->enemy.getY() << " " <<
                l->levelEnemies->enemy.getHealth() << " " <<
                l->levelEnemies->enemy.getDamage() << " " <<
                l->levelEnemies->enemy.getRange() << " " <<
                l->levelEnemies->enemy.getShootingCooldown() << " " <<
                l->levelEnemies->enemy.getCanMove() << " " <<
                l->levelEnemies->enemy.getCanShoot() << " " <<
                l->levelEnemies->enemy.getC() << " ";
            l->levelEnemies = l->levelEnemies->nextEnemy;
        }   
        outputFile << "\n";

        outputFile << l->activePickUps << "\n";

        while(l->levelPickUps != NULL) {
            outputFile <<
                l->levelPickUps->pickUp.getX() << " " <<
                l->levelPickUps->pickUp.getY() << " " <<
                l->levelPickUps->pickUp.getC() << " ";
            l->levelPickUps = l->levelPickUps->nextPickUp;
        }
        outputFile << "\n\n";

        l = l->nextLevel; 
    }

    for(int i = 0; i < MAX_BONUS; i++) {
        outputFile << 
            powerup.bonus[i].IsActive << " " <<
            powerup.bonus[i].OwnedQuantity << " " <<
            powerup.bonus[i].BuyableQuantity << " ";
        if(i == 2 || i == 3 || i == 5) {
            outputFile << powerup.bonus[i].singleEntry << " ";
        }
    }
                
    outputFile.close();
}

// Load the game info from a savefile 
void Save::loadGame(Player &p, Map &m, pLevel &currentLevel, pLevel &first, pLevel &last, PowerUp &powerup) {
    ifstream inputFile;
    inputFile.open("savefile.txt");

    int playerX, playerY, playerHP, playerD, playerR, playerSC, playerP, playerC, playerEK, playerTB, playerCHIT;
    char playerCH;
    inputFile >> playerX >> playerY >> playerHP >> playerD >> playerR >> playerSC >> playerP >> playerC >> playerEK >> playerTB >> playerCHIT;
    inputFile >> ws;
    inputFile.get(playerCH);
    p.setX(playerX); 
    p.setY(playerY);
    p.setC(playerCH);
    p.initializeHealth();
    p.setHealth(playerHP);
    p.setDamage(playerD);  
    p.setRange(playerR); 
    p.setShootingCooldown(playerSC); 
    p.setPoints(playerP);
    powerup.setCoins(playerC);
    p.setEnemiesKilled(playerEK);
    p.setCharacterHits(playerCHIT);
    p.setTotalBullets(playerTB);

    int numOfGeneratedLvls, numOfCurrentLvl, latestTemplate;
    inputFile >> numOfGeneratedLvls >> numOfCurrentLvl >> latestTemplate;
    m.setNumOfGeneratedLevels(numOfGeneratedLvls);
    m.setNumOfCurrentLevel(numOfCurrentLvl);
    m.setLatestTemplate(latestTemplate);

    for(int i = 0; i < numOfGeneratedLvls; i++) {
        int numPlats;
        inputFile >> numPlats;
        Platform currentPlatforms[MAX_PLAT];
        for(int i = 0; i < numPlats; i++) {
            int platX, platY, platL;
            char platC;
            inputFile >> platX >> platY >> platL;
            inputFile >> ws;
            inputFile.get(platC);
            m.copyPlatform(currentPlatforms[i], platX, platY, platL, platC);
        }

        Door currentDoors[NUM_DOOR];
        for(int i = 0; i < NUM_DOOR; i++) {
            int doorX, doorY, doorL, doorR;
            char doorC;
            inputFile >> doorX >> doorY >> doorL >> doorR;
            inputFile >> ws;
            inputFile.get(doorC);
            m.copyDoor(currentDoors[i], doorX, doorY, doorL, doorR, doorC);
        }

        int aliveEnemies;
        inputFile >> aliveEnemies;
        pEnemy currentEnemies = NULL;
        for(int i = 0; i < aliveEnemies; i++) {
            int enemyX, enemyY, enemyHP, enemyD, enemyR, enemySC, enemyCM, enemyCS;
            char enemyC;
            inputFile >> enemyX >> enemyY >> enemyHP >> enemyD >> enemyR >> enemySC >> enemyCM >> enemyCS;
            inputFile >> ws;
            inputFile.get(enemyC);
            Enemy enemy(enemyX, enemyY, enemyC, enemyHP, enemyD, enemyR, enemySC, enemyCM, enemyCS);
            m.addEnemy(currentEnemies, enemy);
        }

        int activePickUps;
        inputFile >> activePickUps;
        pPickUp currentPickUps = NULL;
        for(int i = 0; i < activePickUps; i++) {
            int pickUpX, pickUpY;
            char pickUpC;
            inputFile >> pickUpX >> pickUpY;
            inputFile >> ws;
            inputFile.get(pickUpC);
            PickUp pickup(pickUpX, pickUpY, pickUpC);
            m.addPickUp(currentPickUps, pickup);
        }

        m.addLevel(last, currentPlatforms, currentDoors, currentEnemies, currentPickUps);
        if(i == 0) {
            first = last;
        }
        if(i == numOfCurrentLvl - 1) {
            currentLevel = last;
        }
    }

    for(int i = 0; i < MAX_BONUS; i++) {
        int active, ownedQ, buyableQ, singleE;
        inputFile >> active >> ownedQ >> buyableQ;
        powerup.bonus[i].IsActive = active;
        powerup.bonus[i].OwnedQuantity = ownedQ;
        powerup.bonus[i].BuyableQuantity = buyableQ;
        if(i == 2 || i == 3 || i == 5) {
            inputFile >> singleE;
            powerup.bonus[i].singleEntry = singleE;
        }
    }
    
    inputFile.close();    
}