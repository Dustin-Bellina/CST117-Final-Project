#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <string>
#include <iostream>
#include <fstream>

#include "defs.h"
#include "structs.h"

// map_generation.cpp
void clearScreen();
void drawMap(std::string(*map)[MAP_HEIGHT][MAP_WIDTH]);
void generateRoom(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY);
void generateTown(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2]);

// input_detection.cpp
void inputDetector(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player, int (*playerXY)[2], std::string object);

// movement.cpp
void movementHandler(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int direction, int (*playerXY)[2], std::string& object);
void keys(); // DEBUG - REMOVE

// menus.cpp
void mainMenu(playerType &player);
void townMenu(playerType &player);
void helpMenu();
void inventoryMenu(playerType &player);
void statsMenu(playerType &player);
void shopMenu(playerType &player);
void breadMenu(playerType &player);
void potionMenu(playerType &player);
void swordMenu(playerType &player);
void armorMenu(playerType &player);
void sewerMenu(playerType &player);
void saveGame(playerType& player);
void loadGame(playerType& player);
void initializePlayer(playerType &player);

void menuHandler(playerType &player,std::string &object);

#endif
