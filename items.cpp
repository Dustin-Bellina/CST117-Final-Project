/*
Dustin Bellina

Contains functions relating to item handling

Functions:
isItem() : Return true if the specifi3ed object is an item
pickupItem() : Give the player the item
generateItems() : Generate items in a room of specified parameters
*/

#include <iostream>
#include <string>

#include "defs.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;


bool isItem(string object) {
    for (string ch : ITEM_LIST) {
        if (object == ch) return true;
    }

    return false;
}

void pickupItem(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, string& object) {
    if (object == GOLD) {
        int roll = rollDie(20);
        player.gold += roll;

        if (roll == 1)  message("You picked up 1 gold piece");
        else            message("You picked up " + to_string(roll) + " gold pieces");

        object = "";
    }
    elif (object == BREAD) {
        int roll = rollDie(3);
        player.bread += roll;

        if (roll == 1)  message("You picked up 1 piece of food");
        else            message("You picked up " + to_string(roll) + " rations of food");

        object = "";
    }
    if (object == POTION) {
        int roll = rollDie(100);

        if (roll <= 25) {
            player.strengthPotions += 1;
            message("You piked up a strength potion");
        }
        else {
            player.healthPotions += 1;
            message("You picked up a health potion");
        }

        object = "";
    }
}

// Derived from generateEnemies()@enemies.cpp
void generateItems(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY) {
    int itemCount = 0;

    for (int i = 0; i < MAX_ITEMS + 2 && itemCount < MAX_ITEMS; i++) {
        int ix, iy, roll;
        int attempts = 0;

        do {
            ix = rX + 1 + rand() % ((rX + rW - 1) - rX - 1);
            iy = rY + 1 + rand() % ((rY + rH - 1) - rY - 1);

            attempts++;
        } while ((*map)[0][iy][ix] != FLOOR && attempts < 10);

        if (((*map)[0][iy][ix] != FLOOR) || (isEnemy((*map)[0][iy][ix]))) continue;

        roll = rollDie(100);
        if      (roll <= 33)    (*map)[0][iy][ix] = BREAD;
        elif    (roll <= 66)    (*map)[0][iy][ix] = GOLD;
        else                    (*map)[0][iy][ix] = POTION;

        itemCount++;
    }
}
