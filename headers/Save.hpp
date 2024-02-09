#ifndef SAVE_HPP
#define SAVE_HPP

#include "Player.hpp"
#include "Enemy.hpp"
#include "PickUp.hpp"
#include "Map.hpp"
#include "Door.hpp"
#include <iostream>
#include <fstream>
using namespace std;

class Save {
    public:
        void saveGame(Player p, Map m, pLevel first, PowerUp powerup);
        void loadGame(Player &p, Map &m, pLevel &l, pLevel &first, pLevel &last, PowerUp &powerup);
        void savePowerUp(PowerUp powerup);
        void loadPowerUp(PowerUp &powerup);
};

#endif