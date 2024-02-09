#ifndef INFOGAME_HPP
#define INFOGAME_HPP

#include<ncurses.h>
#include "Player.hpp"

class InfoGame {
    private:
        WINDOW * infoWin;

    public:
        InfoGame();
        void showInfo(Player player, int completedLevels, int currentLevel, PowerUp powerup);
        void showLegenda(Player player, PowerUp powerup);
};

#endif