/*
Functions:
initializePlayer() : Sets default player stats
saveGame() : Saves the player stats to a file
loadGame() : Loads player stats from a file
*/

#include <iostream>
#include <fstream>

#include "defs.h"
#include "structs.h"
#include "prototypes.h"


using namespace std;


void initializePlayer(playerType& player) {
    player.health = 100;
    player.strength = 10;
    player.armor = 25;
    player.healthPotions = 10;
    player.strengthPotions = 5;
    player.swordDamage = 10;
    player.bread = 5;
    player.gold = 100;
}

// i added this because i thought that maybe we'd need it (of course we do)
// for now its just the save and load functions, but we can add more to it later if we need to, 
// like maybe a function to delete the save file or something like that, but for now this is just the basic save and load functionality, 
// it saves all of the player's stats and inventory to a text file and loads them back when you want to continue your game.
// i tested it and it works ok.
void saveGame(playerType& player) {
    ofstream saveFile("savegame.txt");
    if (saveFile.is_open()) {
        saveFile << player.health << endl;
        saveFile << player.strength << endl;
        saveFile << player.armor << endl;
        saveFile << player.healthPotions << endl;
        saveFile << player.strengthPotions << endl;
        saveFile << player.swordDamage << endl;
        saveFile << player.bread << endl;
        saveFile << player.gold << endl;

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
        loadFile >> player.strength;
        loadFile >> player.armor;
        loadFile >> player.healthPotions;
        loadFile >> player.strengthPotions;
        loadFile >> player.swordDamage;
        loadFile >> player.bread;
        loadFile >> player.gold;

        loadFile.close();
        te_print("Game loaded successfully!");
    }
    else {
        te_error("No save file was found!");
    }
}
