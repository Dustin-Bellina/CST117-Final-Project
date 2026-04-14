#ifndef PROTOTYPES_H    // Include guard to prevent multiple inclusions
#define PROTOTYPES_H

#include <iostream>
#include <string>

#include "defs.h"

void clearScreen();
void drawMap(std::string(*map)[MAP_HEIGHT][MAP_WIDTH]);
void generateRoom(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY);
void generateTown(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2]);
void keyDetector(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2], std::string object);
void movementHandler(std::string(*map)[MAP_HEIGHT][MAP_WIDTH], int direction, int (*playerXY)[2], std::string& object);

void keys();

#endif
