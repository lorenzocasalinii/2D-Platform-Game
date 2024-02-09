#include "InfoGame.hpp"

// CONSTRUCTOR
InfoGame::InfoGame() {
    infoWin = newwin(24, 35, 0, 2);
    box(infoWin, 0, 0);
    refresh();
}

// Print game info to the screen
void InfoGame::showInfo(Player player, int generatedLevels, int currentLevel, PowerUp powerup) {
    box(infoWin, 0, 0);

    mvwprintw(infoWin, 2, 4, "STATS ");
    mvwprintw(infoWin, 3, 4, "Points: %d ", player.getPoints());
    mvwprintw(infoWin, 4, 4, "Health: %d ", player.getHealth());
    mvwprintw(infoWin, 5, 4, "Damage: %d ", player.getDamage());
    mvwprintw(infoWin, 6, 4, "Range: %d ", player.getRange());
    mvwprintw(infoWin, 7, 4, "Shooting Cooldown: %d ", player.getShootingCooldown());
    mvwprintw(infoWin, 8, 4, "Coins: %d ", powerup.getCoins());
    mvwprintw(infoWin, 9, 4, "Enemies Killed: %d ", player.getEnemiesKilled());
    mvwprintw(infoWin, 10, 4, "Generated Levels: %d ", generatedLevels);
    mvwprintw(infoWin, 11, 4, "Current Level: %d ", currentLevel);

    mvwprintw(infoWin, 14, 4, "POWERUPS");
    int cont = 0;
    for(int i = 0; i < MAX_BONUS; i++) {
        mvwprintw(infoWin, 15 + cont, 4, "%s", powerup.bonus[i].name);
        if(powerup.bonus[i].IsActive) {
            wattron(infoWin, A_BOLD);
            mvwprintw(infoWin, 15 + cont, 20, "ON");
            wattroff(infoWin, A_BOLD);
        }
        else {
            wattron(infoWin, A_ITALIC);
            mvwprintw(infoWin, 15 + cont, 20, "OFF");
            wattroff(infoWin, A_ITALIC);
        }

        if(powerup.bonus[2].IsActive && i == 2) {
            wattron(infoWin, A_BOLD);
            mvwprintw(infoWin, 15 + cont, 22, "          ");
            mvwprintw(infoWin, 15 + cont, 22, ": %d / 5", 5 - (player.getCharacterHits() - powerup.previousCharacterHits));
            wattroff(infoWin, A_BOLD);
        }
        if(i == 2 && !powerup.bonus[2].IsActive) {
            mvwprintw(infoWin, 15 + cont, 23, "          ");
        }
            
        if(powerup.bonus[3].IsActive && i == 3) {
            wattron(infoWin, A_BOLD);
            mvwprintw(infoWin, 15 + cont, 22, "          ");
            mvwprintw(infoWin, 15 + cont, 22, ": %d / 5", 5 - (player.getEnemiesKilled() - powerup.previousEnemiesKilled));
            wattroff(infoWin, A_BOLD);
        }
        if(i == 3 && !powerup.bonus[3].IsActive) {
            mvwprintw(infoWin, 15 + cont, 23, "          ");
        }
            
        if(powerup.bonus[5].IsActive && i == 5) {
            wattron(infoWin, A_BOLD);
            mvwprintw(infoWin, 15 + cont, 22, "          ");
            mvwprintw(infoWin, 15 + cont, 22, ": %d / 10", 10 - (player.getTotalBullets() - powerup.previousBulletsShot));
            wattroff(infoWin, A_BOLD);
        }
        if(i == 5 && !powerup.bonus[5].IsActive) {
            mvwprintw(infoWin, 15 + cont, 23, "          ");
        }

        cont++;
    }
    wrefresh(infoWin);
}


// Print powerup info to the screen
void InfoGame::showLegenda(Player player, PowerUp powerup){
    
    WINDOW * Legenda = newwin(9, 62, 24, 40);
    box(Legenda, 0, 0);
    wrefresh(Legenda);
    mvwprintw(Legenda, 1, 4, "Use the arrow keys to move");
    mvwprintw(Legenda, 2, 4, "Press q and e to shoot");
    mvwprintw(Legenda, 3, 4, "Press 1 to activate the SHIELD, you have %d of them", powerup.bonus[2].OwnedQuantity);
    mvwprintw(Legenda, 4, 4, "Press 2 to activate the MINIGUN,you have %d of them", powerup.bonus[3].OwnedQuantity);
    mvwprintw(Legenda, 5, 4, "Press 3 to activate the SUPER-JUMP, you have %d of them", powerup.bonus[4].OwnedQuantity);
    mvwprintw(Legenda, 6, 4, "Press 4 to activate the POWER-SHOTS, you have %d of them", powerup.bonus[5].OwnedQuantity);
    mvwprintw(Legenda, 7, 4, "Press ESC to pause the game");
    wrefresh(Legenda);
    
    if(!player.getIsAlive()){
        werase(Legenda);
        wrefresh(Legenda);
        delwin(Legenda);
    }
}