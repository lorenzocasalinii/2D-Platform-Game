#ifndef MAP_HPP
#define MAP_HPP

#include <ncurses.h>
#include <ctime>
#include "MapDefaultValues.hpp"
#include "PowerUp.hpp"

struct Level {
    Level* nextLevel = NULL;                            
    Level* previousLevel = NULL;                        
    int levelTemplate = 0;                                  
    Platform levelPlatforms[MAX_PLAT];                  
    int numPlats = 0;                                   
    pEnemy levelEnemies = NULL;                         
    int aliveEnemies = 0;                               
    Door levelDoors[2];                                
    pPickUp levelPickUps = NULL;                        
    int activePickUps = 0;                              
};
typedef Level* pLevel;

class Map { 
    private:
        int oldTemplate;                            // Template del livello generato in precedenza
        int latestTemplate;                         // Template dell'ultimo livello generato
        int numOfGeneratedLevels;                   // Numero di nuove stanze generate
        int numOfCurrentLevel;                      // Numero della stanza attuale
        int numEnemies;                             // Numero massimo di nemici per stanza
        int numPickUps;                             // Numero massimo di pickup per stanza
        int incrH;                                  // Numero per gestire aumento vita dei nemici
        int incrD;                                  // Numero per gestire aumento danno dei nemici

    public:
        Map();
        
        void pickRandomLevel();

        void createNewLevel(pLevel &currentLevel);

        void copyPlatform(Platform &toLoad, int x, int y, int l, char c);
        void copyDoor(Door &toLoad, int x, int y, int l, bool r, char c);
        Enemy copyEnemy(Enemy toCopy);
        PickUp copyPickUp(PickUp toCopy);
        
        void loadNewLevel(Platform p[], Door d[], pEnemy &newEnemies, pPickUp &newPickUps);

        void addLevel(pLevel &LAST, Platform p[], Door d[], pEnemy e, pPickUp pu);
        void addEnemy(pEnemy &head, Enemy e);
        void addPickUp(pPickUp &head, PickUp pu);
                
        void printMap(WINDOW * win, pLevel currentLevel);
        void printEnemies(WINDOW * win, pEnemy e);
        void printPickUps(WINDOW * win, pPickUp e);

        void resetBulletLists(pBullet &player, pBullet &enemy);
        void emptyBulletList(pBullet &head);

        void deleteEnemies(WINDOW  * win, pEnemy e);

        void increaseDifficulty();
        void increaseDifficultyPowerup(PowerUp powerup);

        int getLatestTemplate();
        int getOldTemplate();
        int getNumOfGeneratedLevels();
        int getNumOfCurrentLevel();

        void setLatestTemplate(int p);
        void setOldTemplate(int p);
        void setNumOfGeneratedLevels(int s);
        void setNumOfCurrentLevel(int s);
};

#endif 