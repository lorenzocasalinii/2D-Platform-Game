#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <ncurses.h>
#include "Game.hpp"
#include "Shop.hpp"

class GameMode {
    private:
        int option;
        
    public:
        GameMode(int option);
        void launch(WINDOW * gameWin);
};

#endif