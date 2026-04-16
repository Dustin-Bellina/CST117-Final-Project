#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "defs.h"
#include "structs.h"

// map_generation.cpp
void clearScreen();
void drawMap(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], std::string object = "");
void clearMap(std::string(*map)[MAP_HEIGHT][MAP_WIDTH]);
void generateRoom(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY, std::vector<std::pair<int, int>> doors = {});
void generateHall(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int x1, int y1, int x2, int y2);
void generateTown(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player);
void generateSewer(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player);

// input_detection.cpp
void inputDetector(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player);

// movement.cpp
void movementHandler(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int direction, playerType &player, std::string &object);
void keys(); // DEBUG - REMOVE

// menus.cpp
void menuHandler(std::string (*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player,std::string &object);
void signHandler(playerType &player);
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


// text_engine.cpp
void te_print(std::string message);
void te_error(std::string message);
void more();
void wait();

#endif
