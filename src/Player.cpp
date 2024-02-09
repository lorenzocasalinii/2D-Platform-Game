#include "Player.hpp"

// CONSTRUCTORS
Player::Player() {}

Player::Player(int width, int height, char c) : Character(width, height, c) {
    xVelocity = 0;
    yVelocity = 0;
    newX = 0;
    newY = 0;
    x = -1;
    y = -1;
    points = 0;
    range = 25; 
    health = 200;       
    damage = 25;
    enemiesKilled = 0;
    shootingCooldown = 20;
    onEnemy = false;
    enterNextLevel = false;
    enterPreviousLevel = false;
    jumpStrength = 4;
    totalBullets = 0;
    freezeEnemies = false;
    freezeEnemies = 0;
    characterHits = 0;
}


// Place the player in front of the door
void Player::spawnPlayer(int spawnX, int spawnY) {
    x = spawnX;
    y = spawnY;
    flushinp();
}


// Handle user input
void Player::handleInput(pBullet &head, bool &saveFile, PowerUp &powerup) {
    int userInput = getch(); 
    switch(userInput) {
        // Movement
        case KEY_LEFT:
            xVelocity = -1;
            break;
        case KEY_RIGHT:
            xVelocity = 1;
            break;  
        case KEY_UP:
            if(!isJumping) {
                yVelocity = -jumpStrength;
                isJumping = true;
            }
            break;
        // Shoot
        case 'e':
            if(shootingCounter > shootingCooldown) {
                shoot(head, true);
                totalBullets++;
            }
            break;
        case 'q':
            if(shootingCounter > shootingCooldown) {
                shoot(head, false);
                totalBullets++;
            }
            break;
        // Activate powerup
        case '1':
            if (powerup.bonus[2].OwnedQuantity > 0) {
                powerup.bonus[2].IsActive = true;
                powerup.bonus[2].OwnedQuantity -= 1;
            }
            break;
        case '2':
            if (powerup.bonus[3].OwnedQuantity > 0) {
                powerup.bonus[3].IsActive = true;
                powerup.bonus[3].OwnedQuantity -= 1;
            }
            break;
        case '3':
            if (powerup.bonus[4].OwnedQuantity > 0) {
                powerup.bonus[4].IsActive = true;
                powerup.bonus[4].OwnedQuantity -= 1;
            }
            break;
        case '4':
            if (powerup.bonus[5].OwnedQuantity > 0) {
                powerup.bonus[5].IsActive = true;
                powerup.bonus[5].OwnedQuantity -= 1;
            }
            break;          
        // Save and exit from the game
        case 27:
            WINDOW * tempWin = newwin(9, 26, 5, 6); 
            box(tempWin, 0, 0);
            nodelay(stdscr, false);
            mvwprintw(tempWin, 2, 3, "To quit the game:");
            mvwprintw(tempWin, 3, 3, "Press 'ESC'");
            mvwprintw(tempWin, 5, 3, "To keep playing:");
            mvwprintw(tempWin, 6, 3, "Press any other key");
            wrefresh(tempWin);
            int input = getch();
            if(input == 27)
                saveFile = true;
            delwin(tempWin);
            nodelay(stdscr, true);
            break;
    } 

    shootingCounter++;
    if(userInput == ERR && !isJumping) {
        xVelocity = 0;
        yVelocity = 0;
    }
    // Handle freeze pickup
    if(freezeEnemies && freezeEnemiesCounter < 100) {
        freezeEnemiesCounter++;
    }
    else {
        freezeEnemies = false;
        freezeEnemiesCounter = 0;
    }
}

// Calculate new position and handle collisions with the map
void Player::updatePlayer(pLevel &currentLevel, WINDOW * win, PowerUp &powerup) {
    if(y < yMax - 2 || yVelocity < 0) {
        yVelocity += gravity;
        isJumping = true;
    }

    newX = x + xVelocity;
    newY = y + yVelocity;

    handleBoxCollisions();
    handleEnemyCollisions(currentLevel->levelEnemies, win);
    handleEnviromentCollisions(win);
    handlePickUpCollisions(currentLevel->levelPickUps, win, powerup, currentLevel->activePickUps);
    handleDoorCollisions(currentLevel->levelDoors, (currentLevel->previousLevel == NULL));
    
    x = newX;
    y = newY;
}


// Handle enemy actions
void Player::triggerEnemies(WINDOW * win, pEnemy &e, pBullet &head) {
    pEnemy temp = e;
    if(!freezeEnemies) {
        while(temp != NULL) {
            temp->enemy.startShooting(x, y, head, win);       
            temp->enemy.move(win);    
            temp = temp->nextEnemy;
        }
    }
}


// Handle collisions with the borders of the map
void Player::handleBoxCollisions() {
    if (newX < 1) 
        newX = 1;
    if (newX > xMax - 2) 
        newX = xMax - 2;
    if (newY < 1) 
        newY = 1;
    if (newY > yMax - 2) {
        newY = yMax - 2;
        isJumping = false;
        yVelocity = 0;
    }
}

// Handle collisions with platforms and walls
void Player::handleEnviromentCollisions(WINDOW * win) {
    char newpos = mvwinch(win, newY, newX); 
    handlePlatformCollisions(win, newpos);
    handleWallCollisions(win, newpos);
}

// Handle collisions with platforms
void Player::handlePlatformCollisions(WINDOW * win, char newpos) {
    // The player is jumping
    if(yVelocity < 0) {
        handleJumpingOnPlatform(win, newpos);
    }
    // The player is either falling or on a platform
    else {
        handleFallingOnPlatform(win, newpos);
    }
}

// Allow the player to stand on top of a platform
void Player::handleFallingOnPlatform(WINDOW * win, char newpos) {
    if(newpos == '=') {
        isJumping = false;
        newY = newY - 1;
        yVelocity = 0;
    }

    int temp = y;
    while(temp < newY) {
        temp++;
        char nextYpos = mvwinch(win, temp, newX);
        if(nextYpos == '=') {
            isJumping = false;
            yVelocity = 0;
            newY = temp - 1;
        }
    }
}

// Allow the player to jump on a platform
void Player::handleJumpingOnPlatform(WINDOW * win, char newpos) {
    if(newpos == '=') {
        newY++;
    } 
}

// Handle walls collisions
void Player::handleWallCollisions(WINDOW * win, char newpos) {
    // Lateral collisions
    if(newpos == '|') {
        handleBlockedByWall(win);

        newpos = mvwinch(win, newY, newX);
        if(yVelocity >= 0) {
            handleFallingOnPlatform(win, newpos);
        }
    }  
    // Collisions from below
    int temp = y;
    while(temp > newY) {
        temp--;
        char nextYpos = mvwinch(win, temp, newX);
        if(nextYpos == '|') {
            isJumping = false;
            yVelocity = 0;
            newY = temp + 1;
        }
    }
}

// Allow the player not to go through walls
void Player::handleBlockedByWall(WINDOW * win) {
    if(xVelocity > 0) {
        newX--; 
    }
    else if(xVelocity < 0) {
        newX++; 
    }
}

// Handle doors collisions
void Player::handleDoorCollisions(Door d[], bool isFirstRoom) {
    for(int i = 0; i < NUM_DOOR; i++) {
        
        int doorX = d[i].getX();
        int doorY = d[i].getY();
        int doorHeight = d[i].getL();
        bool doorRight = d[i].getR();

        if(newX == doorX || (doorRight ? (newX <= doorX && x > doorX) : (newX >= doorX && x < doorX))) {
            if(newY <= doorY && newY > doorY - doorHeight) {
                if(i == 0) {
                    if(!isFirstRoom) {
                        enterPreviousLevel = true;
                    }
                    else {
                        doorRight ? (newX++) : (newX--);
                    } 
                }
                else {
                    enterNextLevel = true;
                }
            }
        }
    }
}

// Handle the physical collisions with enemies
void Player::handleEnemyCollisions(pEnemy e, WINDOW * win) {
    while(e != NULL) {
        int enemyX = e->enemy.getX();
        int enemyY = e->enemy.getY();
        int enemyD = e->enemy.getDamage();
        bool enemyCanMove = e->enemy.getCanMove();
        bool enemyMovingRight = e->enemy.getMoveRight();
        if(enemyX == newX && (enemyY == y || enemyY == newY || (enemyY > y && enemyY <= newY) || (enemyY < y && enemyY >= newY))) {                
            // The player is moving right
            if(xVelocity < 0) {
                newX += 5;
                xVelocity = 1;
            }
            // The player is moving left
            else if(xVelocity > 0) {
                newX -= 5;
                xVelocity = -1;
            }
            // The player isn't moving
            else {
                if(enemyCanMove) {
                    if(enemyMovingRight) {
                        newX += 5;
                        xVelocity = 1;
                    }
                    else {
                        newX -= 5;
                        xVelocity = -1;
                    }
                }
                else {
                    if(enemyY < y && enemyY >= newY) {
                        newY +=3;
                    }
                    else if(enemyY > y && enemyY <= newY) {
                        newY -=3;
                    }
                    isJumping = true;
                }
            }
            setHealth(-enemyD);
            flushinp();
        }       
        e = e->nextEnemy;
    }
    handleEnviromentCollisions(win);
    handleBoxCollisions();
}

// Handle the collisions with pickups
void Player::handlePickUpCollisions(pPickUp &pu, WINDOW * win, PowerUp &powerup, int &activePickups) {
    pPickUp temp = pu;
    while(temp != NULL) {
        if((newX == temp->pickUp.getX()) && (newY == temp->pickUp.getY())) {
            if(temp->pickUp.getC() == '$') {
                powerup.addCoins(100);
            }
            else if(temp->pickUp.getC() == '+') {
                health += 100;
            }
            else {
                freezeEnemies = true;
            }
            pu = removePickUp(pu, temp->pickUp);
            activePickups--;
        }
        temp = temp->nextPickUp;
    }
}


// Remove pickup from a list
pPickUp Player::removePickUp(pPickUp p, PickUp toRemove) {
    pPickUp temp = p;
    bool leave = false;
        while(temp != NULL && !leave) {
            if((temp->pickUp.getX() == toRemove.getX()) && (temp->pickUp.getY() == toRemove.getY())) {
                if(temp->previousPickUp != NULL) {
                    temp->previousPickUp->nextPickUp = temp->nextPickUp;
                } 
                else {
                    p = temp->nextPickUp;
                }
                if(temp->nextPickUp != NULL) {
                    temp->nextPickUp->previousPickUp = temp->previousPickUp;
                }
                delete temp;
                leave = true;
            }
            temp = temp->nextPickUp;
        }
    return p;
}

// HELPER FUNCTIONS TO MOVE THE PLAYER INSIDE THE SHOP
void Player::moveDownShop(){
    y++;
    if(y > yMax - 2)
        y = yMax - 2 ;
}

void Player::moveUpShop(){
    if(y != 3 || x > 5){
        y--;
        if(y < 1)
            y = 1;
    }
}

void Player::moveLeftShop() {
    if(y > 2 || x != 6){
        x--;
        if(x < 1)
            x = 1;
    }
}

void Player::moveRightShop() {
    x++;
    if(x > xMax - 2)
        x = xMax - 2;
}


// Handle powerup that must be active from the start
void Player::CheckStartPowerUps(PowerUp &powerup) {
    if(powerup.bonus[0].IsActive) { 
        health = 400; 
        if(powerup.bonus[0].OwnedQuantity > 0)
            powerup.bonus[0].OwnedQuantity -= 1;
    }

    if(powerup.bonus[1].IsActive){
        damage = 50;
        if(powerup.bonus[1].OwnedQuantity > 0)
            powerup.bonus[1].OwnedQuantity -= 1;
    }  
}

// Handle powerup that must be activated with user input
void Player::CheckInGamePowerUps(PowerUp &powerup, pBullet &bullet, WINDOW * gameWin) { 

    // Minigun
    if(powerup.bonus[3].IsActive) { 
        shootingCooldown = 5;
    }
    else {
        shootingCooldown = 20;
    }
    
    // Super Jump
    if(powerup.bonus[4].IsActive) {   
        jumpStrength = 6;
    } 
    else {
        jumpStrength = 4;
    }
        
    // Power Shots
    if(powerup.bonus[5].IsActive) {
        range = 60;
        damage = 60;
        pBullet temp = bullet;
        while(temp != NULL) {
            if(temp->b.getDirection()) {
                temp->b.setBulletChar('}');
            }
            else {  
                temp->b.setBulletChar('{');
            }
            temp = temp->nextBullet;
        }
    } 
    else {
        range = 20;
        if(powerup.bonus[1].IsActive) {
            damage = 50;
        } 
        else {
            damage = 25;
        }
    }

    // Second Life
    if(powerup.bonus[6].IsActive) {  
        
        if(!getIsAlive()){
            bool stop = true;
            WINDOW * boxSecondLife = newwin(11, 28, 5, 5); 
            box(boxSecondLife, 0, 0);
            nodelay(stdscr, false);
            init_pair(1, COLOR_GREEN, COLOR_BLACK);
            wattron(boxSecondLife, COLOR_PAIR(1));
            mvwprintw(boxSecondLife, 2, 2, "SECOND LIFE:");
            wattroff(boxSecondLife, COLOR_PAIR(1));
            mvwprintw(boxSecondLife, 4, 2, "To use your second life:");
            mvwprintw(boxSecondLife, 5, 2, "Press TAB");
            mvwprintw(boxSecondLife, 7, 2, "To quit the game:");
            mvwprintw(boxSecondLife, 8, 2, "Press ESC");
            wrefresh(boxSecondLife);
            while(stop) {
                int input = getch();
                switch (input) {
                    case 9:
                        isAlive = true;
                        stop = false;
                        powerup.bonus[6].OwnedQuantity -= 1;
                        health += 100;
                        freezeEnemies = true;
                        break;
                    case 27:
                        stop = false;
                        powerup.bonus[6].IsActive = false;
                        werase(stdscr);
                        wrefresh(stdscr);
                        break;  
                }  
            }
            werase(boxSecondLife);
            wrefresh(boxSecondLife);
            delwin(boxSecondLife);
            nodelay(stdscr, true);
        }      
    }  
}


// Activate visual effects for powerups
void Player::PowerUpsEffects(PowerUp &powerup, WINDOW *win) {
    // Extra health
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    if(powerup.bonus[0].IsActive && health > 200 && !powerup.bonus[2].IsActive) //vita aumentata    
        wattron(win, COLOR_PAIR(1));
    
    // Shield
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
    if(powerup.bonus[2].IsActive) 
        wattron(win, COLOR_PAIR(4));
    
    // Minigun
    if(powerup.bonus[3].IsActive)  
        wattron(win, A_ITALIC);
    
    // Super Jump
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    if(powerup.bonus[4].IsActive) 
        wattron(win, COLOR_PAIR(5));
    
    // Power Shots
    if(powerup.bonus[5].IsActive) 
        wattron(win, A_BOLD);
}


// Deactivate powerups that are consumed
void Player::deactivateInGamePowerUps(PowerUp &powerup) {
    
    // Deactivate the Shield after taking 5 shots
    if(powerup.bonus[2].singleEntry && powerup.bonus[2].IsActive){
        powerup.bonus[2].singleEntry = false;
        powerup.previousCharacterHits = characterHits;
    }
    if(characterHits - powerup.previousCharacterHits == 5){
        powerup.bonus[2].IsActive = false;
        powerup.bonus[2].singleEntry = true;
    }

    // Deactivate Super Jump as soon as you leave the current level
    if(((enterNextLevel || enterPreviousLevel) && powerup.bonus[4].IsActive )){
        powerup.bonus[4].IsActive = false;
    }

    // Deactivate Minigun after 5 kills
    if(powerup.bonus[3].singleEntry && powerup.bonus[3].IsActive){
        powerup.bonus[3].singleEntry = false;
        powerup.previousEnemiesKilled = enemiesKilled;  
    }
    if(enemiesKilled - powerup.previousEnemiesKilled == 5){ 
        powerup.bonus[3].IsActive = false;
        powerup.bonus[3].singleEntry = true;
    }
  
    // Deactivate Power Shots after 10 bullets
    if(powerup.bonus[5].singleEntry && powerup.bonus[5].IsActive){
        powerup.bonus[5].singleEntry = false;
        powerup.previousBulletsShot = totalBullets;
    }
    if(totalBullets - powerup.previousBulletsShot >= 10){
        powerup.bonus[5].IsActive = false;
        powerup.bonus[5].singleEntry = true;
    }

    // Deactivate Second Life
    if(powerup.bonus[6].OwnedQuantity == 0){
        powerup.bonus[6].IsActive = false;
    }
}

// Print the player with visual effects if he has powerups 
void Player::drawCharacterPlayer(WINDOW *win, PowerUp powerup) {
    PowerUpsEffects(powerup, win);
    mvwaddch(win, y, x, c);
    wattroff(win, A_ATTRIBUTES);
}

// GETTERS
int Player::getPoints() {
    return points;
}

bool Player::getEnterNextLevel(){
    return enterNextLevel;
}

bool Player::getEnterPreviousLevel(){
    return enterPreviousLevel;
}

int Player::getEnemiesKilled() {
    return enemiesKilled;
}

int Player::getTotalBullets(){
    return totalBullets;
}

int Player::getCharacterHits(){
    return characterHits;
}


// SETTERS
void Player::setPoints(int p) {
    points += p;
}


void Player::setEnterNextLevel(bool b){
    enterNextLevel = b;
}

void Player::setEnterPreviousLevel(bool b){
    enterPreviousLevel = b;
}

void Player::setEnemiesKilled(int k) {
    enemiesKilled += k;
}

void Player::setTotalBullets(int b) {
    totalBullets = b;
}

void Player::setCharacterHits(int x) {
    characterHits += x;
}

void Player::setJumpStrength(int j){
    jumpStrength = j;
}

void Player::setFreezeEnemies(bool fe) {
    freezeEnemies = fe;
}