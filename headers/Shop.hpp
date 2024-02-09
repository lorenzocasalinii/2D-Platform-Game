#ifndef SHOP_HPP
#define SHOP_HPP

#include <ncurses.h>
#include "PowerUp.hpp"
#include "Game.hpp"
#include "Menu.hpp"

class Shop {
    private:
        int yMax, xMax;

    public:
        Shop();
        void createShopWin(WINDOW * win);
        bool runShop(WINDOW * shopWin, WINDOW * gameWin, bool reset, Game game, PowerUp &powerup);

        void PayDecrease(WINDOW * win, int x, int y, PowerUp &powerup, Player &player);
        
        bool DeathWindow();
        void shopChoiceWindow(WINDOW * boxChoice, int  i);
        void coinsWindow(WINDOW * shopWin, PowerUp powerup);
};

#endif
