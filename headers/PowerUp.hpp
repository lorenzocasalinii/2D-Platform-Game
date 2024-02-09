#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <ncurses.h>
#include <cstring>
#include "Bullet.hpp"
#define MAX_BONUS 7

struct Bonus{
    int BuyableQuantity;
    int Cost;
    int xRBox;
    int xLBox;
    int yBox;
    int OwnedQuantity;
    bool IsActive;
    char name[30];
    bool singleEntry = true;
};

class PowerUp{
    private:
        int coins;
    public:
        Bonus bonus[MAX_BONUS];
        PowerUp();
        int previousBulletsShot = 0;
        int previousEnemiesKilled = 0;
        int previousCharacterHits = 0;

        void createBonus(WINDOW *shopwin);

        void setBuyableBonus(int x, int i);
        void setOwnedBonus(int i);
        void setActiveStartPowerUps();

        void setCoins(int c);
        void addCoins(int c);
        int getCoins();
};

#endif
