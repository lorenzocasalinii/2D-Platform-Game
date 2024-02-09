#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"
#include "Map.hpp"
#include "PowerUp.hpp"

class Player : public Character {

    private:
        int points;
        bool isJumping;
        int xVelocity;
        int yVelocity;
        int newX;
        int newY;
        int gravity = 1;
        int jumpStrength;
        int enemiesKilled;
        bool onEnemy;
        bool enterNextLevel;
        bool enterPreviousLevel;
        int totalBullets;                       
        int characterHits;                      
        bool freezeEnemies;
        int freezeEnemiesCounter;               
    
    public: 
        Player();
        Player(int width, int height, char c);

        void spawnPlayer(int spawnX, int spawnY);

        void handleInput(pBullet &head, bool &saveFile, PowerUp &powerup);
        void updatePlayer(pLevel &currentLevel, WINDOW * win, PowerUp &powerup);

        void triggerEnemies(WINDOW * win, pEnemy &e, pBullet &head);
        
        void handleBoxCollisions();
        
        void handleEnviromentCollisions(WINDOW * win);
        void handlePlatformCollisions(WINDOW * win, char c);
        void handleFallingOnPlatform(WINDOW * win, char c);
        void handleJumpingOnPlatform(WINDOW * win, char c);
        void handleWallCollisions(WINDOW * win, char c);
        void handleBlockedByWall(WINDOW * win);
        
        void handleEnemyCollisions(pEnemy e, WINDOW * win);
        
        void handleDoorCollisions(Door d[], bool isFirstRoom);
        
        void handlePickUpCollisions(pPickUp &pu, WINDOW * win, PowerUp &powerup, int &activePickups);
        pPickUp removePickUp(pPickUp pu, PickUp toRemove);
                
        void moveLeftShop();
        void moveRightShop();
        void moveUpShop();
        void moveDownShop();

        void CheckStartPowerUps(PowerUp &powerup);
        void CheckInGamePowerUps(PowerUp &powerup, pBullet &bullet, WINDOW * gameWin);
        void PowerUpsEffects(PowerUp &powerup, WINDOW *win);
        void deactivateInGamePowerUps(PowerUp &powerup);
        void drawCharacterPlayer(WINDOW * win, PowerUp powerup);

        int getPoints();
        bool getEnterNextLevel();
        bool getEnterPreviousLevel();
        int getEnemiesKilled();
        int getTotalBullets();
        int getCharacterHits();

        void setEnterNextLevel(bool b);
        void setEnterPreviousLevel(bool b);
        void setPoints(int p);
        void setEnemiesKilled(int k);
        void setTotalBullets(int b);
        void setCharacterHits(int x);
        void setJumpStrength(int j);
        void setFreezeEnemies(bool fe);
};

#endif
