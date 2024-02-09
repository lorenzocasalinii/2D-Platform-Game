#include "Menu.hpp"
#include "GameMode.hpp"

int main() {
    
    // Ncurses setup
    initscr();
    noecho();
    cbreak();
    curs_set(0); 
    nodelay(stdscr, true);
    keypad(stdscr, true);

    // Menu setup
    Menu menu;
    start_color();
    bkgd(COLOR_BLACK);
    menu.createMenuWin();

    // Game initialization
    WINDOW * gameWin = newwin(24, 148, 0, 40); 
    GameMode gamemode(menu.getChoice());
    gamemode.launch(gameWin);

    endwin();
    return 0;
}