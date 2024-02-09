#include "Shop.hpp"

Shop::Shop(){}

// Create Shop Window
void Shop::createShopWin(WINDOW * ShopWin) {
    box(ShopWin, 0, 0);
    getmaxyx(ShopWin, yMax, xMax);
    refresh();
    wrefresh(ShopWin);
}


// Contain the Shop logic
bool Shop::runShop(WINDOW * shopWin, WINDOW * gameWin, bool reset, Game game, PowerUp &powerup) {    
    
    // Create the player to move inside the shop
    Player player(xMax, yMax, '@');
    player.setX(xMax/2);
    player.setY(6);
    player.drawCharacterPlayer(shopWin, powerup);

    bool exitShop = false;
    bool playerDied = true;

    while(!exitShop) {     

        mvwprintw(shopWin, 22, 160, "Press TAB to play");

        int userInput = getch(); 
        switch(userInput) {
            case KEY_LEFT:
                player.moveLeftShop();
                break;
            case KEY_RIGHT:
                player.moveRightShop();
                break;  
            case KEY_UP:
                player.moveUpShop();
                break;
            case KEY_DOWN:
                player.moveDownShop();
                break;
            // Press TAB to start the game
            case 9: 
                game.createGameWin(gameWin);
                wclear(shopWin);
                wrefresh(shopWin);
                delwin(shopWin);
                playerDied = game.run(gameWin, reset, powerup);  //playerDied is true if the player is dead and false if the player left the game
                exitShop = true;
                break;
        }
        // If the player died print the death window
        if(exitShop && playerDied) {
            bool restart = DeathWindow();
            return restart;
        } 

        // Else stay inside the shop
        else {
            powerup.createBonus(shopWin);    
            coinsWindow(shopWin, powerup);

            int y = player.getY();
            int x = player.getX();

            PayDecrease(shopWin, x, y, powerup, player); 
            // Check for powerups that must be activated as soon as you buy them
            powerup.setActiveStartPowerUps();    

            player.drawCharacterPlayer(shopWin, powerup);
            wrefresh(shopWin);
            player.deleteCharacter(shopWin);
            napms(25); 
        }  
    }
    return false;
}

// Handle the buy powerup logic
void Shop::PayDecrease(WINDOW *win , int x, int y, PowerUp &powerup, Player  &player) {
    bool stop = true;
    
    for(int i = 0; i < MAX_BONUS; i++) {   
        // If the player enter inside the powerup box and if there are is enough money
        if(x < powerup.bonus[i].xRBox && x > powerup.bonus[i].xLBox  && y == powerup.bonus[i].yBox  && powerup.bonus[i].BuyableQuantity != 0 && powerup.bonus[i].Cost <= powerup.getCoins()){

            // Create powerup window
            WINDOW * boxChoice = newwin(14, 100, 5, 43);
            shopChoiceWindow(boxChoice, i);
            wrefresh(boxChoice);    
 
            while(stop) {
                int Input = getch();
                switch (Input){
                // Buy
                case 9:
                    powerup.addCoins(-powerup.bonus[i].Cost);
                    powerup.setBuyableBonus(powerup.bonus[i].BuyableQuantity - 1, i);
                    powerup.setOwnedBonus(i);
                    stop = false;
                    werase(boxChoice);
                    wrefresh(boxChoice);
                    delwin(boxChoice);
                    break;
                // Don't buy
                case 27:
                    stop = false;
                    werase(boxChoice);
                    wrefresh(boxChoice);
                    delwin(boxChoice);
                    break;      
                }  
            }  
            delwin(boxChoice);
            player.moveDownShop();
            player.moveDownShop(); 
            player.moveDownShop();
            player.moveDownShop();              
            }  
        }
    }   

// Create the coins window
void Shop :: coinsWindow(WINDOW * shopWin, PowerUp powerup){
    WINDOW * boxMoney = subwin(shopWin, 3, 7, 0, 0); 
    box(boxMoney, 0, 0); 
    wrefresh(boxMoney);  
    mvwprintw(shopWin, 1, 1, "     ");
    mvwprintw(shopWin, 1, 1, "%d$", powerup.getCoins());
}



// Create the death window
bool Shop::DeathWindow(){
    init_pair(6, COLOR_WHITE, COLOR_GREEN);  
    init_pair(7, COLOR_WHITE, COLOR_RED);  
    init_pair(3, COLOR_RED, COLOR_BLACK); 
    bool stop = true;
    int start_y = 3;
    int start_x = 93;
    WINDOW * AfterDeathChoice= newwin(24, 188, 0, 0);
    box(AfterDeathChoice, 0, 0);  
    wattron(AfterDeathChoice, COLOR_PAIR(3));
    mvwprintw(AfterDeathChoice, start_y + 5,  start_x-34, "____    ____  ______    __    __      _______   __   _______  _______   __  ");
    mvwprintw(AfterDeathChoice, start_y + 6,  start_x-34, "\\   \\  /   / /  __  \\  |  |  |  |    |       \\ |  | |   ____||       \\ |  | ");
    mvwprintw(AfterDeathChoice, start_y + 7,  start_x-34, " \\   \\/   / |  |  |  | |  |  |  |    |  .--.  ||  | |  |__   |  .--.  ||  |    ");
    mvwprintw(AfterDeathChoice, start_y + 8, start_x-34, "  \\_    _/  |  |  |  | |  |  |  |    |  |  |  ||  | |   __|  |  |  |  ||  |    ");
    mvwprintw(AfterDeathChoice, start_y + 9, start_x-34, "    |  |    |  `--'  | |  `--'  |    |  '--'  ||  | |  |____ |  '--'  ||__|    ");
    mvwprintw(AfterDeathChoice, start_y + 10, start_x-34, "    |__|     \\______/   \\______/     |_______/ |__| |_______||_______/ (__)    ");
    wattroff(AfterDeathChoice, COLOR_PAIR(3));
    mvwprintw(AfterDeathChoice, start_y + 15, start_x-14, "Do you want to start again?" );
    wattron(AfterDeathChoice, COLOR_PAIR(6));
    mvwprintw(AfterDeathChoice, start_y + 17, 43, "Yes/TAB" );
    wattroff(AfterDeathChoice, COLOR_PAIR(6));
    wattron(AfterDeathChoice, COLOR_PAIR(7));
    mvwprintw(AfterDeathChoice, start_y + 17, 128, "No, quit the game/ESC" );
    wattroff(AfterDeathChoice, COLOR_PAIR(7));
    wrefresh(AfterDeathChoice);
    bool choice;
    while(stop){
        int Input = getch();
            switch(Input){
                // If the user wants to play again
                case 9:
                    stop = false;
                    choice = true;
                    werase(AfterDeathChoice);
                    wrefresh(AfterDeathChoice);
                    delwin(AfterDeathChoice);
                    break;
                case 27:
                // If the user wants to leave the game
                    stop = false;
                    choice = false;
                    werase(AfterDeathChoice);
                    wrefresh(AfterDeathChoice);
                    delwin(AfterDeathChoice);
                    break;      
            }  
    }  
    return choice;
}


// Create the specific window for each powerup
void Shop::shopChoiceWindow(WINDOW * boxChoice, int i) {
      
    box(boxChoice, 0, 0);
    mvwprintw(boxChoice, 10, 42, "Are you sure?");

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    wattron(boxChoice, COLOR_PAIR(1));
    mvwprintw(boxChoice, 12, 21, "Yes/TAB");
    wattroff(boxChoice, COLOR_PAIR(1)); 

    init_pair(3,COLOR_RED, COLOR_BLACK);
    wattron(boxChoice, COLOR_PAIR(3));
    mvwprintw(boxChoice, 12, 71, "No/ESC");
    wattroff(boxChoice, COLOR_PAIR(3)); 

    if(i == 0) {
        wattron(boxChoice, COLOR_PAIR(1));
        mvwprintw(boxChoice, 3,40,"       ::         ");
        mvwprintw(boxChoice, 4,40,"       ::         ");
        mvwprintw(boxChoice, 5,40,"   ::::::::::      ");
        mvwprintw(boxChoice, 6,40,"       ::         ");
        mvwprintw(boxChoice, 7,40,"       ::         ");
        wattroff(boxChoice, COLOR_PAIR(1));
        mvwprintw(boxChoice, 4, 10, "The increased life");
        mvwprintw(boxChoice, 5, 10, "will give you 200");
        mvwprintw(boxChoice, 6, 10, "extra health points.");
        mvwprintw(boxChoice, 7, 10, "It deactivates when you die.");
    }

    if(i == 6) {
        wattron(boxChoice, COLOR_PAIR(3));
        mvwprintw(boxChoice, 2, 44, "  **   **  ");
        mvwprintw(boxChoice, 3, 44, " **** **** ");
        mvwprintw(boxChoice, 4, 44, "***********");
        mvwprintw(boxChoice, 5, 44," ********* ");
        mvwprintw(boxChoice, 6, 44,"  *******  ");
        mvwprintw(boxChoice, 7, 44,"    ***    ");
        mvwprintw(boxChoice, 8, 44,"     *     ");
        wattroff(boxChoice, COLOR_PAIR(3));
        mvwprintw(boxChoice, 4, 10, "You can respawn");
        mvwprintw(boxChoice, 5, 10, "after you die.");
        mvwprintw(boxChoice, 6, 10, "It deactives after using.");
    }

    if(i == 4) {
        wattron(boxChoice, COLOR_PAIR(5));
        mvwprintw(boxChoice, 3, 46, "   ^   ");
        mvwprintw(boxChoice, 4, 46, "  / \\  ");
        mvwprintw(boxChoice, 5, 46, " /   \\ ");
        mvwprintw(boxChoice, 6, 46, "-------");
        mvwprintw(boxChoice, 7, 46, "  | |  ");
        mvwprintw(boxChoice, 8, 46, "  | |  ");
        wattroff(boxChoice, COLOR_PAIR(5));
        mvwprintw(boxChoice, 4, 10, "If you activate it");
        mvwprintw(boxChoice, 5, 10, "your jump height");
        mvwprintw(boxChoice, 6, 10, "will boost.");
        mvwprintw(boxChoice, 7, 10, "It deactivates after");
        mvwprintw(boxChoice, 8, 10, "changing level.");
    }

    if(i == 1) {
        wattron(boxChoice, COLOR_PAIR(3));
        mvwprintw(boxChoice, 2, 33, "   _  ___________________,");
        mvwprintw(boxChoice, 3, 33, "   \\ \\@([            ]_________)");
        mvwprintw(boxChoice, 4, 33, "    \\ \\@([            ]_________)");
        mvwprintw(boxChoice, 5, 33, "   _/\\----[________]");
        mvwprintw(boxChoice, 6, 33, "  //    / ((    )");
        mvwprintw(boxChoice, 7, 33, " /_____|");
        mvwprintw(boxChoice, 8, 33, "\\_____/");
        wattroff(boxChoice, COLOR_PAIR(3));
        mvwprintw(boxChoice, 4, 10, "The increased damage");
        mvwprintw(boxChoice, 5, 10, "will boost your");
        mvwprintw(boxChoice, 6, 10, "gun damage by 25.");
        mvwprintw(boxChoice, 7, 10, "It deactivates when");
        mvwprintw(boxChoice, 8, 10, "you die.");
    }

    if(i == 3) {
        wattron(boxChoice, COLOR_PAIR(5));
        mvwprintw(boxChoice, 3, 40, "____________.");
        mvwprintw(boxChoice, 4, 40, ":::::;;;;;;||::::=====:");
        mvwprintw(boxChoice, 5, 36, "|:::::::::|:::::||:::=====:");
        mvwprintw(boxChoice, 6, 36, "|::::::::;|:|^^|^^");
        mvwprintw(boxChoice, 7, 36, "|:::::::  | |");
        mvwprintw(boxChoice, 8, 44, "__| |");
        wattroff(boxChoice, COLOR_PAIR(5));
        mvwprintw(boxChoice, 4, 10, "If you activate it");
        mvwprintw(boxChoice, 5, 10, "your shooting cooldown");
        mvwprintw(boxChoice, 6, 10, "will decrease.");
        mvwprintw(boxChoice, 7, 10, "It deactivates after");
        mvwprintw(boxChoice, 8, 10, "5 eliminations.");
    }
    
    if(i == 2) {
    init_pair(12, COLOR_BLUE, COLOR_BLACK);
    wattron(boxChoice, COLOR_PAIR(12));
    mvwprintw(boxChoice, 3, 41, "      _______");
    mvwprintw(boxChoice, 4, 41, "     /   |   \\");
    mvwprintw(boxChoice, 5, 41, "    /____|____\\");
    mvwprintw(boxChoice, 6, 41, "    \\    |    /");
    mvwprintw(boxChoice, 7, 41, "     \\   |   /");
    mvwprintw(boxChoice, 8, 41, "      \\_____/");
    wattroff(boxChoice, COLOR_PAIR(12));
    mvwprintw(boxChoice, 4, 10, "If you activate it");
    mvwprintw(boxChoice, 5, 10, "you won't get damaged");
    mvwprintw(boxChoice, 6, 10, "by bullets");
    mvwprintw(boxChoice, 7, 10, "It deactivates after 5 hits.");
    }

    if(i == 5) {
        init_pair(13, COLOR_MAGENTA, COLOR_BLACK);
        wattron(boxChoice, COLOR_PAIR(13));
        mvwprintw(boxChoice, 4, 35, " _______/]_________[\\___________");
        mvwprintw(boxChoice, 5, 35, "|    ____     ___|---------------|=====");
        mvwprintw(boxChoice, 6, 35, "|_ /      /  /_|  |");
        mvwprintw(boxChoice, 7, 35, "         /_/    \\_/");
        wattroff(boxChoice, COLOR_PAIR(13));
        mvwprintw(boxChoice, 4, 10, "If you activate it");
        mvwprintw(boxChoice, 5, 10, "your shooting range");
        mvwprintw(boxChoice, 6, 10, "and your damage ");
        mvwprintw(boxChoice, 7, 10, "will increase.");
        mvwprintw(boxChoice, 8, 10, "It deactivates after 10 shots.");
    }
}



