/*
Alir Louis

Contains functions to set up and save the game

Functions:
initializePlayer() : Sets default player stats
saveGame() : Saves the player stats to a file
loadGame() : Loads player stats from a file
*/

#include <iostream>
#include <fstream>

#include "structs.h"
#include "prototypes.h"


using namespace std;


void initializePlayer(playerType& player) {
    player.health = 10;
    player.maxHealth = 10;
    player.strength = 10;
    player.armorClass = 10;
    player.healthPotions = 10;
    player.strengthPotions = 5;
    player.bread = 5;
    player.gold = 100;

    player.level = 1;
    player.xp = 0;

    player.stage = "TOWN";
    player.sublevel = 0;

    player.x = 0;
    player.y = 0;
}

void saveGame(playerType& player) {
    ofstream saveFile("savegame.txt");
    if (saveFile.is_open()) {
        saveFile << player.health << endl;
        saveFile << player.maxHealth << endl;
        saveFile << player.strength << endl;
        saveFile << player.armorClass << endl;
        saveFile << player.healthPotions << endl;
        saveFile << player.strengthPotions << endl;
        saveFile << player.bread << endl;
        saveFile << player.gold << endl;

        saveFile << player.level << endl;
        saveFile << player.xp << endl;

        saveFile << player.stage << endl;
        saveFile << player.sublevel - 1 << endl;

        saveFile.close();
        te_print("Game saved successfully!");
    }
    else {
        te_error("An error has occured: Game was not saved!");
    }
}

void loadGame(playerType& player) {
    ifstream loadFile("savegame.txt");
    if (loadFile.is_open()) {
        loadFile >> player.health;
        loadFile >> player.maxHealth;
        loadFile >> player.strength;
        loadFile >> player.armorClass;
        loadFile >> player.healthPotions;
        loadFile >> player.strengthPotions;
        loadFile >> player.bread;
        loadFile >> player.gold;

        loadFile >> player.level;
        loadFile >> player.xp;

        loadFile >> player.stage;
        loadFile >> player.sublevel;

        loadFile.close();
        te_print("Game loaded successfully!");
    }
    else {
        te_error("No save file was found!");
    }
}
