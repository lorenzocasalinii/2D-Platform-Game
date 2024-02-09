#ifndef GAME_HPP
#define GAME_HPP
#include <ncurses.h>
#include "Save.hpp"
#include "InfoGame.hpp"
#include "BulletHelper.hpp"
using namespace std;

class Game {
    private:
        int xMax, yMax;
    public:
        Game(int xM, int yM);
        void createGameWin(WINDOW * win);
        void clearGameWin(WINDOW * win);
        bool run(WINDOW * gameWin, bool reset, PowerUp &powerup);
};

#endif