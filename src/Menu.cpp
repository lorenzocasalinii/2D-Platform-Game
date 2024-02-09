#include "Menu.hpp"

// Create the Menu window
void Menu::createMenuWin() {
    getmaxyx(stdscr, yMax, xMax);
    menuWin = newwin(4, 50, yMax/2 - 2, xMax/2 - 25);
    box(menuWin, 0, 0);
    wrefresh(menuWin);
    keypad(menuWin, true);
    runMenu();
    werase(menuWin);
    wrefresh(menuWin);
    delwin(menuWin);
}

// Create and run the menu
void Menu::runMenu() {
    bool leaveMenu = false;
    ifstream fileStream("savefile.txt");
    // Print the options
    while(!leaveMenu) {
        for(int i = 0; i < 2; i++){
            if(i == highlight)
                wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, i+1, 1, "%s", menuChoices[i]);
            wattroff(menuWin, A_REVERSE);
        }
        cursor = wgetch(menuWin);
        switch(cursor) {
            case KEY_UP:
                if(highlight > 0)
                    highlight--;
                else
                    highlight = 1;
                break;
            case KEY_DOWN:
                if(highlight < 1)
                    highlight++;
                else
                    highlight = 0;
                break;
            case 10:
                // If you press 'Continue Game' without having a savefile
                if(fileStream.fail() && highlight == 1) {
                    WINDOW * errWin = newwin(4, 35, yMax/2 - 2, xMax/2); 
                    box(errWin, 0, 0);
                    nodelay(errWin, false);
                    init_pair(100, COLOR_RED, COLOR_BLACK);
                    wattron(errWin, COLOR_PAIR(100));
                    mvwprintw(errWin, 1, 2, "There's no savefile! :C ");
                    wattroff(errWin, COLOR_PAIR(100));
                    mvwprintw(errWin, 2, 2, "Press any other key to go back.");
                    wattroff(errWin, COLOR_PAIR(100));
                    wrefresh(errWin);
                    wgetch(menuWin);
                    nodelay(errWin, true);  
                    wclear(errWin);
                    wrefresh(errWin);
                    delwin(errWin);
                    box(menuWin, 0, 0);
                }
                // If you want to create a new game or load one from a savefile
                else {
                    choice = highlight;
                    leaveMenu = true;
                }
                break;
            default:
                break;
        }
    }
}

// GETTER
bool Menu::getChoice() {
    return choice;
}


