#ifndef MENU_HPP
#define MENU_HPP

#include<ncurses.h>
#include <iostream>
#include <fstream>
using namespace std;

class Menu {
    private:
        int xMax, yMax;
        int cursor = 0;
        int choice;
        const char* menuChoices[2] = {"New Game", "Continue Game"};
        int highlight = 0;
        WINDOW * menuWin;
    
    public:
        void createMenuWin();
        void runMenu();
        bool getChoice();
};

#endif
