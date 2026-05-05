#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "structs.h"

class Enemy;

// RNG
int rollDie(int sides, int rolls = 1);

// Text Engine
void message(std::string msg);
void flushMessages();
void te_print(std::string msg);
void te_error(std::string msg);
void te_success(std::string msg);
void more();
void wait();

// Screen/Map Drawing
void clearScreen();
void clearMapSpace();
void drawMap(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::string object = "");
void drawCell(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int x, int y, std::string object = "");
roomType drawRoom(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int x, int y);
void clearMap(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], std::vector<Enemy*>& enemies);

// Map Generation
void loadLevel(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies, std::string level = "");
void generateRoom(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY, std::vector<std::pair<int, int>> doors = {});
void generateHall(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int x1, int y1, int x2, int y2);
void generateTown(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies);
void generateSewer(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies);
void generateCave(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies);
void generateForest(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies);
void generateCastle(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies);

// Enemy Generation
void generateEnemies(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], std::vector<Enemy*>& enemies, std::string stage, int rW, int rH, int rX, int rY);
void generateBoss(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], std::vector<Enemy*>& enemies, std::string stage, int rW, int rH, int rX, int rY);
Enemy* spawnSewerEnemy();
Enemy* spawnCaveEnemy();
Enemy* spawnForestEnemy();
Enemy* spawnCastleEnemy();

// Movement
void movementHandler(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int direction, playerType& player, std::string& object, std::vector<Enemy*>& enemies);
void inputDetector(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies, std::string& object);

// Enemy Logic
bool  isEnemy(std::string object);
void  attackEnemy(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies, int x, int y);
void  damageEnemy(playerType& player, Enemy* enemy);
void  killEnemy(playerType& player, std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], std::vector<Enemy*>& enemies, Enemy* enemy, int vectorPos);
void  clearEnemies(std::vector<Enemy*>& enemies);
void  killMessage(std::string enemyName);
void  enemyTurn(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, Enemy* enemy);
void  attackPlayer(playerType& player, int damage);
void  moveEnemy(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, Enemy* enemy);

// Object/Pickup Handling
bool isItem(std::string object);
void pickupItem(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::string& object);
void generateItems(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY);

// Menus / UI
void mainMenu(playerType& player);
void menuHandler(std::string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, std::vector<Enemy*>& enemies, std::string& object);
void breadMenu(playerType& player);
void inventoryMenu(playerType& player);
void statsMenu(playerType& player);
void helpMenu();
void displayStatus(playerType& player);
void enemyStatus(std::vector<Enemy*>& enemies);
void potionMenu(playerType& player);
void shopMenu(playerType& player);
void signHandler(playerType& player);
void deathMenu(playerType& player);
void winMenu(playerType& player);

void healPlayer(playerType& player, int healAmount);

// Data Management
void initializePlayer(playerType& player);
void saveGame(playerType& player);
void loadGame(playerType& player);

// Level & XP Handling
void awardXP(playerType& player, int xp);
void levelHandler(playerType& player);

// Cursor Control
void hideCursor();
void showCursor();

#endif
