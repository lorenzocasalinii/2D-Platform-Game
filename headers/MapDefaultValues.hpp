#ifndef MAP_DEFAULT_VALUES_HPP
#define MAP_DEFAULT_VALUES_HPP

#include "Platform.hpp"
#include "Enemy.hpp"
#include "Door.hpp"
#include "PickUp.hpp"

class MapDefaultValues {
    public:
        // Template 0
        int platX0[MAX_PLAT] = {1, 11, 1, 11, 1, 11, 1, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 23, 53, 83, 100, 100, 100, 105, 105, 105, 105, 105, 105, 105, 105, 108, 142 };
        int platY0[MAX_PLAT] = {3,6,9,12, 15, 18, 21, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 18, 15, 12, 9, 6, 3, 4, 5, 6, 7, 8, 9, 10, 11, 7, 18};
        int platL0[MAX_PLAT] = {10, 10, 10, 10, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 30, 30, 64, 3, 3, 10, 1, 1, 1, 1, 1, 1, 1, 1, 15, 5 };
        char platC0[MAX_PLAT] = {'=','=','=', '=','=','=','=', '|', '|', '|', '|', '|', '|', '|',  '|', '|', '|', '|', '|', '|', '|',  '|', '|', '|', '|', '|', '|', '|', '=', '=', '=', '=', '=', '=', '|',  '|', '|', '|', '|', '|', '|', '|', '=', '='};
        
        Door door0[NUM_DOOR] = {Door(1, 2, 2, true, '['), Door(146, 11, 4, false, ']')}; 
        
        int enemyX0[MAX_ENEMY] = {10, 20, 10, 50, 90, 112, 68, 90, 120, 140};
        int enemyY0[MAX_ENEMY] ={8, 11, 20, 17, 11, 11, 14, 22, 22, 22 };
        char enemyC0[MAX_ENEMY] = {'O', 'T', '&', 'O', 'T', '&', 'O', 'T', '&', 'O'};
        int enemyHP0[MAX_ENEMY] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
        int enemyD0[MAX_ENEMY] = {30, 20, 10, 30, 20, 10, 30, 20, 10, 30};
        int enemyR0[MAX_ENEMY] = {0, 30, 20, 0, 30, 20, 0, 30, 20, 0};
        int enemySC0[MAX_ENEMY] = {0, 20, 30, 0, 20, 30, 0, 20, 30, 0};
        bool enemyCM0[MAX_ENEMY] = {true, false, true, true, false, true, true, false, true, true};
        bool enemyCS0[MAX_ENEMY] = {false, true, true, false, true, true, false, true, true, false};
        
        int pickUpX0[MAX_PICKUP] = {146, 1, 105, 23};
        int pickUpY0[MAX_PICKUP] = {17, 22, 2, 17};
        char pickUpC0[MAX_PICKUP] = {'$', '*', '$', '+'};

        
        // Template 1
        int platX1[MAX_PLAT] = {1, 8, 10, 15, 60, 80, 95, 115};
        int platY1[MAX_PLAT] = {5, 10, 15, 20, 15, 15, 11, 6};
        int platL1[MAX_PLAT] = {8, 12, 20, 120, 3, 14, 20, 31};
        char platC1[MAX_PLAT] = {'=', '=', '=', '=', '=', '=', '=', '='};
        
        Door door1[NUM_DOOR] = {Door(1, 4, 4, true, '['), Door(143, 5, 5, false, ']')};
        
        int enemyX1[MAX_ENEMY] = {10, 12, 28, 25, 60, 100, 120, 88, 110, 125 };
        int enemyY1[MAX_ENEMY] ={9, 14, 14, 19, 19, 19, 19, 14, 10, 5}; 
        char enemyC1[MAX_ENEMY] = {'O', 'T', '&', 'O', 'T', '&', 'O', 'T', '&', 'O'};
        int enemyHP1[MAX_ENEMY] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
        int enemyD1[MAX_ENEMY] = {30, 20, 10, 30, 20, 10, 30, 20, 10, 30};
        int enemyR1[MAX_ENEMY] = {0, 30, 20, 0, 30, 20, 0, 30, 20, 0};
        int enemySC1[MAX_ENEMY] = {0, 20, 30, 0, 20, 30, 0, 20, 30, 0};
        bool enemyCM1[MAX_ENEMY] = {true, false, true, true, false, true, true, false, true, true};
        bool enemyCS1[MAX_ENEMY] = {false, true, true, false, true, true, false, true, true, false};
        
        int pickUpX1[MAX_PICKUP] = {1, 146, 15, 61};
        int pickUpY1[MAX_PICKUP] = {22, 22, 19, 14};
        char pickUpC1[MAX_PICKUP] = {'$', '$', '*', '+'};


        // Template 2
        int platX2[MAX_PLAT] = {1, 133, 128, 80, 80, 45, 10, 20, 20, 1};
        int platY2[MAX_PLAT] = {5, 5, 18, 21, 15, 12, 21, 17, 13, 10};
        int platL2[MAX_PLAT] = {131, 14, 10, 40, 45, 40, 50, 5, 5, 46};
        char platC2[MAX_PLAT] = {'=', '=', '=', '=', '=', '=', '=', '=', '=', '='};
        
        Door door2[NUM_DOOR] = {Door(1, 4, 4, true, '[' ), Door(1, 9, 4, true, '[')};
        
        int enemyX2[MAX_ENEMY] = {135, 128, 137, 70, 15, 15, 3, 40, 20, 24 };
        int enemyY2[MAX_ENEMY] ={4, 17, 17, 11, 9, 20, 22, 4, 16, 12}; 
        char enemyC2[MAX_ENEMY] = {'O', 'T', '&', 'O', 'T', '&', 'O', 'T', '&', 'O'};
        int enemyHP2[MAX_ENEMY] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
        int enemyD2[MAX_ENEMY] = {30, 20, 10, 30, 20, 10, 30, 20, 10, 30};
        int enemyR2[MAX_ENEMY] = {0, 30, 20, 0, 30, 20, 0, 30, 20, 0};
        int enemySC2[MAX_ENEMY] = {0, 20, 30, 0, 20, 30, 0, 20, 30, 0};
        bool enemyCM2[MAX_ENEMY] = {true, false, true, true, false, true, true, false, true, true};
        bool enemyCS2[MAX_ENEMY] = {false, true, true, false, true, true, false, true, true, false};
        
        int pickUpX2[MAX_PICKUP] = {1, 44, 40, 23};
        int pickUpY2[MAX_PICKUP] = {22, 9, 20, 16};
        char pickUpC2[MAX_PICKUP] = {'$', '$', '*', '+'};

        
        // Template 3
        int platX3[MAX_PLAT] = {1, 1, 1, 1, 2, 60, 130, 130, 130, 130, 121, 100, 75, 50, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21};
        int platY3[MAX_PLAT] = {18, 14, 10, 6, 3, 18, 18, 14, 10, 6, 3, 5, 8, 6, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 19, 15, 11, 7};
        int platL3[MAX_PLAT] = {12, 12, 12, 12, 22, 3, 17, 17, 17, 17, 20, 25, 35, 25, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3};
        char platC3[MAX_PLAT] = {'=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '|', '=', '=', '=', '='};
        
        Door door3[NUM_DOOR] = {Door(1, 22, 4, true, '['), Door(50,5, 5, true, '[')};
        
        int enemyX3[MAX_ENEMY] = {12, 70, 131, 80, 131, 100, 12, 12, 12, 12};
        int enemyY3[MAX_ENEMY] ={17, 22, 13, 7, 5, 22, 13, 9, 5, 2};
        char enemyC3[MAX_ENEMY] = {'O', 'T', '&', 'O', 'T', '&', 'O', 'T', '&', 'O'};
        int enemyHP3[MAX_ENEMY] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
        int enemyD3[MAX_ENEMY] = {30, 20, 10, 30, 20, 10, 30, 20, 10, 30};
        int enemyR3[MAX_ENEMY] = {0, 30, 20, 0, 30, 20, 0, 30, 20, 0};
        int enemySC3[MAX_ENEMY] = {0, 20, 30, 0, 20, 30, 0, 20, 30, 0};
        bool enemyCM3[MAX_ENEMY] = {true, false, true, true, false, true, true, false, true, true};
        bool enemyCS3[MAX_ENEMY] = {false, true, true, false, true, true, false, true, true, false};
        
        int pickUpX3[MAX_PICKUP] = {5, 61, 9, 103};
        int pickUpY3[MAX_PICKUP] = {22, 17, 2, 4};
        char pickUpC3[MAX_PICKUP] = {'*', '+', '$', '$'};

        // Template 4
        int platX4[MAX_PLAT] = {2, 20, 83, 134, 144, 5, 26, 133, 133, 5};
        int platY4[MAX_PLAT] = {3, 3, 3, 3, 6, 9, 9, 20, 17, 13};
        int platL4[MAX_PLAT] = {17, 62, 50, 13, 3, 20, 121, 5, 5, 142};
        char platC4[MAX_PLAT] = {'=', '=', '=', '=', '=', '=', '=', '=', '=', '='};
        
        Door door4[NUM_DOOR] = {Door(2, 2, 2, true, '['), Door(5, 12, 3, true, '[')};
        
        int enemyX4[MAX_ENEMY] = {82, 19, 25, 30, 138, 140, 10, 90, 5, 30};
        int enemyY4[MAX_ENEMY] ={3, 3, 9, 2, 2, 8, 12, 12, 22, 22}; 
        char enemyC4[MAX_ENEMY] = {'#', '#', '#', 'O', 'T', '&', 'O', 'T', '&', 'O'};
        int enemyHP4[MAX_ENEMY] = {0, 0, 0, 20, 20, 20, 20, 20, 20, 20};
        int enemyD4[MAX_ENEMY] = {40, 40, 40, 30, 20, 10, 30, 20, 10, 30};
        int enemyR4[MAX_ENEMY] = {0, 0, 0 ,0, 30, 20, 0, 30, 20, 0};
        int enemySC4[MAX_ENEMY] = {0, 0, 0, 0, 20, 30, 0, 20, 30, 0};
        bool enemyCM4[MAX_ENEMY] = {false, false, false, true, false, true, true, false, true, true};
        bool enemyCS4[MAX_ENEMY] = {false, false, false, false, true, true, false, true, true, false};
        
        int pickUpX4[MAX_PICKUP] = {50, 80, 1, 134 };
        int pickUpY4[MAX_PICKUP] = {2, 8, 22, 19};
        char pickUpC4[MAX_PICKUP] = {'$', '$', '*', '+'};


        // Template 5
        int platX5[MAX_PLAT] = {1, 135, 10, 111, 5, 1, 140};
        int platY5[MAX_PLAT] = {17, 19, 11, 11, 14, 5, 7};
        int platL5[MAX_PLAT] = {132, 6, 100, 36, 7, 140, 4};
        char platC5[MAX_PLAT] = {'=', '=','=','=','=', '=','='};
        
        Door door5[NUM_DOOR] = {Door(1, 22, 5, true, '[' ), Door(1, 4, 4, true, '[')};
        
        int enemyX5[MAX_ENEMY] = {111, 110, 70, 60, 20, 80, 140, 100, 40, 130};
        int enemyY5[MAX_ENEMY] ={11, 11, 22, 16, 4, 10, 18, 22, 22, 4}; 
        char enemyC5[MAX_ENEMY] = {'#', '#', 'O', 'T', '&', 'O', 'T', '&', 'O', 'T'};
        int enemyHP5[MAX_ENEMY] = {0, 0, 20, 20, 20, 20, 20, 20, 20};
        int enemyD5[MAX_ENEMY] = {40, 40, 25, 25, 25, 25, 25, 25, 25, 25};
        int enemyR5[MAX_ENEMY] = {0, 0, 30, 20, 10, 30, 20, 10, 30, 20};
        int enemySC5[MAX_ENEMY] = {0, 0, 0, 20, 30, 0, 20, 30, 0, 20};
        bool enemyCM5[MAX_ENEMY] = {false, false, true, false, true, true, false, true, true, false};
        bool enemyCS5[MAX_ENEMY] = {false, false, false, true, true, false, true, true, false, true};
        
        int pickUpX5[MAX_PICKUP] = {10, 146, 1, 142 };
        int pickUpY5[MAX_PICKUP] = {22, 22, 16, 6};
        char pickUpC5[MAX_PICKUP] = {'*', '$', '$', '+'};


        // Template 6
        int platX6[MAX_PLAT] = {1, 11, 21, 121, 137, 10, 12, 14, 16, 18, 20, 22, 69, 80, 125, 129, 1};
        int platY6[MAX_PLAT] = {12, 8, 4, 8, 12, 13, 14, 15, 16, 17, 18, 19, 14, 22, 18, 15, 18};
        int platL6[MAX_PLAT] = {10, 10, 100, 14, 10, 3, 3, 3, 3, 3, 3, 50, 3, 50, 5, 8, 3};
        char platC6[MAX_PLAT] = {'=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '='};
        
        Door door6[NUM_DOOR] = {Door(1, 11, 3, true, '['), Door(146, 11, 3, false, ']')};
        
        int enemyX6[MAX_ENEMY] = {17, 30, 60, 95, 35, 55, 130, 95, 120, 22};
        int enemyY6[MAX_ENEMY] ={7, 3, 3, 3, 18, 18, 7, 21, 21, 22}; 
        char enemyC6[MAX_ENEMY] = {'O', 'T', '&', 'O', 'T', '&', 'O', 'T', '&', 'O'};
        int enemyHP6[MAX_ENEMY] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
        int enemyD6[MAX_ENEMY] = {30, 20, 10, 30, 20, 10, 30, 20, 10, 30};
        int enemyR6[MAX_ENEMY] = {0, 30, 20, 0, 30, 20, 0, 30, 20, 0};
        int enemySC6[MAX_ENEMY] = {0, 20, 30, 0, 20, 30, 0, 20, 30, 0};
        bool enemyCM6[MAX_ENEMY] = {true, false, true, true, false, true, true, false, true, true};
        bool enemyCS6[MAX_ENEMY] = {false, true, true, false, true, true, false, true, true, false};
        
        int pickUpX6[MAX_PICKUP] = {1,70, 22, 120 };
        int pickUpY6[MAX_PICKUP] = {17, 13, 3, 3};
        char pickUpC6[MAX_PICKUP] = {'$', '+', '*', '$'};


        // Template 7
        int platX7[MAX_PLAT] = {1, 12, 43, 124, 144, 95, 8, 15, 30, 50, 80, 100, 110, 135, 135, 135, 95, 95};
        int platY7[MAX_PLAT] = {3, 3, 3, 3, 3, 7, 22, 19, 16, 13, 16, 19, 22, 18, 14, 10, 13, 9};
        int platL7[MAX_PLAT] = {10, 30, 80, 19, 3, 52, 9, 20, 20, 30, 20, 20, 30, 5, 5, 5, 3, 3};
        char platC7[MAX_PLAT] = {'=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '='};
        
        Door door7[NUM_DOOR] = {Door(1, 2, 2, true, '['), Door(146, 6, 3, false, ']')};
        
        int enemyX7[MAX_ENEMY] = {42, 123, 30, 50, 65, 85, 110, 135, 23, 40,};
        int enemyY7[MAX_ENEMY] ={3, 3, 2, 2, 12, 2, 18, 21, 18, 15}; 
        char enemyC7[MAX_ENEMY] = {'#', '#', 'O', 'T', '&', 'O', 'T', '&', 'O', 'T'};
        int enemyHP7[MAX_ENEMY] = {0, 0, 20, 20, 20, 20, 20, 20, 20};
        int enemyD7[MAX_ENEMY] = {40, 40, 25, 25, 25, 25, 25, 25, 25, 25};
        int enemyR7[MAX_ENEMY] = {0, 0, 30, 20, 10, 30, 20, 10, 30, 20};
        int enemySC7[MAX_ENEMY] = {0, 0, 0, 20, 30, 0, 20, 30, 0, 20};
        bool enemyCM7[MAX_ENEMY] = {false, false, true, false, true, true, false, true, true, false};
        bool enemyCS7[MAX_ENEMY] = {false, false, false, true, true, false, true, true, false, true};
        
        int pickUpX7[MAX_PICKUP] = {1, 90, 146, 137};
        int pickUpY7[MAX_PICKUP] = {22, 22, 2, 17};
        char pickUpC7[MAX_PICKUP] = {'$', '*', '$', '+'};
};

#endif