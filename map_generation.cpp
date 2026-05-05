/*
Dustin Bellina

Contains functions relating to map generation and drawing

Functions:
	clearScreen() :  clears the screen
	clearMapSpace() : Clear the space where the map is drawn
	clearMap() :  Clears the map array **Does not display the cleared map
	drawMap() :  Displays the map
	drawCell() : Draws the specified cell on the map
	drawRoom() : Draw an entire room in the map

	loadLevel() : Generate the specified level

	generateRoom() :  Generates a room of specified parameters
	generateHall() :  Uses Bresenham's line algorithm to generate hallways in the map

	generateTown()
	generateSewer()
	generateCave()
	generateForest()
	generateCastle()
*/

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "classes.h"
#include "structs.h"
#include "prototypes.h"


using namespace std;


void clearScreen() {
	cout << CURSOR_HOME;
	for (int i = 0; i < SCREEN_HEIGHT + 4; i++) {
		cout << CLEAR_LINE << "\033[1B" << flush;
	}
	cout << CURSOR_HOME;
}

void clearMapSpace() {
	cout << "\033[2;0H";
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		cout << CLEAR_LINE << "\033[1B" << flush;
	}
	cout << CURSOR_HOME;
}

void clearMap(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], vector<Enemy*>& enemies) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			(*map)[0][i][j] = " ";
			(*map)[1][i][j] = "0";
		}
	}

	clearEnemies(enemies);
}

void drawMap(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, string object) {
	clearMapSpace();

	if (DEBUG_MAP) {
		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
				(*map)[1][i][j] = "1";
	}

	string mapCell;
	string revealed;

	cout << "\033[2;0H";	// Reserve the top line for text

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			mapCell = (*map)[0][i][j];
			revealed = (*map)[1][i][j];

			if (revealed == "1" || mapCell == PLAYER) {
				if ((object == HALL) && (mapCell == PLAYER)) {
					cout << BG_GREY << mapCell << RESET_STYLE;
				}
				elif(mapCell == HALL) {
					cout << FG_GREY << BG_GREY << mapCell << RESET_STYLE;
				}
				else {
					cout << mapCell;
				}
			}
			else {
				cout << " ";
			}
		}
		cout << "\n";
	}
}

void drawCell(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int x, int y, string object) {
	string mapCell = (*map)[0][y][x];

	cout << "\033[" << y + 2 << ";" << x + 1 << "f";

	if ((object == HALL) && (mapCell == PLAYER)) {
		cout << BG_GREY << mapCell << RESET_STYLE;
	}
	elif(mapCell == HALL) {
		cout << FG_GREY << BG_GREY << mapCell << RESET_STYLE;
	}
	else {
		cout << mapCell;
	}

	cout << flush;

	(*map)[1][y][x] = "1";
}

roomType drawRoom(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int x, int y) {
	int ix = x;
	int iy = y;

	if ((iy > 0) && ((*map)[0][iy - 1][ix] == FLOOR)) { iy--; }
	elif((iy < MAP_HEIGHT - 1) && (((*map)[0][iy + 1][ix] == FLOOR) || (isEnemy((*map)[0][iy + 1][ix])) || (isItem((*map)[0][iy + 1][ix])))) { iy++; }
	elif((ix > 0) && ((*map)[0][iy][ix - 1] == FLOOR)) { ix--; }
	elif((ix < MAP_WIDTH - 1) && (((*map)[0][iy][ix + 1] == FLOOR) || (isEnemy((*map)[0][iy][ix + 1])) || (isItem((*map)[0][iy][ix + 1])))) { ix++; }
	else	return { -1, -1, -1, -1 };

	int startX = ix, endX = ix, startY = iy, endY = iy;

	while ((startX > 0) &&
		((*map)[0][iy][startX] != SIDE_WALL) &&
		((*map)[0][iy][startX] != TL_WALL) &&
		((*map)[0][iy][startX] != BL_WALL) &&
		((*map)[0][iy][startX] != DOOR) &&
		((*map)[0][iy][startX] != HALL))
	{
		startX--;
	}

	while ((endX < MAP_WIDTH - 1) &&
		((*map)[0][iy][endX] != SIDE_WALL) &&
		((*map)[0][iy][endX] != TR_WALL) &&
		((*map)[0][iy][endX] != BR_WALL) &&
		((*map)[0][iy][endX] != DOOR) &&
		((*map)[0][iy][endX] != HALL))
	{
		endX++;
	}

	while ((startY > 0 &&
		((*map)[0][startY][ix] != TB_WALL)) &&
		((*map)[0][startY][ix] != TL_WALL) &&
		((*map)[0][startY][ix] != TR_WALL) &&
		((*map)[0][startY][ix] != DOOR) &&
		((*map)[0][startY][ix] != HALL))
	{
		startY--;
	}

	while ((endY < MAP_HEIGHT - 1) &&
		((*map)[0][endY][ix] != TB_WALL) &&
		((*map)[0][endY][ix] != BL_WALL) &&
		((*map)[0][endY][ix] != BR_WALL) &&
		((*map)[0][endY][ix] != DOOR) &&
		((*map)[0][endY][ix] != HALL))
	{
		endY++;
	}

	for (int i = startY; i <= endY; i++) {
		for (int j = startX; j <= endX; j++)
			(*map)[1][i][j] = "1";
	}

	return { startX, startY, endX, endY };
}

void loadLevel(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, vector<Enemy*>& enemies, string level) {
	clearMap(map, enemies);

	if (level == "") { level = player.stage; }

	if (level == "TOWN") { generateTown(map, player, enemies); }
	elif(level == "SEWER") { generateSewer(map, player, enemies); }
	elif(level == "CAVE") { generateCave(map, player, enemies); }
	elif(level == "FOREST") { generateForest(map, player, enemies); }
	elif(level == "CASTLE") { generateCastle(map, player, enemies); }
	else { te_error("Unexpected player.stage: " + player.stage); showCursor(); exit(1); }
}

void generateRoom(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY, vector<pair<int, int>> doors) {
	for (int i = 0; i < rH; i++) {
		for (int j = 0; j < rW; j++) {
			bool top = (i == 0);
			bool bottom = (i == rH - 1);
			bool left = (j == 0);
			bool right = (j == rW - 1);

			if (top && left)		(*map)[0][i + rY][j + rX] = TL_WALL;
			elif(top && right)		(*map)[0][i + rY][j + rX] = TR_WALL;
			elif(bottom && left)	(*map)[0][i + rY][j + rX] = BL_WALL;
			elif(bottom && right)	(*map)[0][i + rY][j + rX] = BR_WALL;
			elif(top || bottom)		(*map)[0][i + rY][j + rX] = TB_WALL;
			elif(left || right)		(*map)[0][i + rY][j + rX] = SIDE_WALL;
			else					(*map)[0][i + rY][j + rX] = FLOOR;
		}
	}

	for (auto& door : doors)
		(*map)[0][door.second][door.first] = DOOR;
}

// Implementation of Bresenham's line algorithm: https://gist.github.com/ssavi-ict/092501c69e2ffec65e96a8865470ad2f enhanced for this purpose by ai
void generateHall(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int x1, int y1, int x2, int y2) {
	int dx = abs(x2 - x1), sx = (x1 < x2) ? 1 : -1;
	int dy = -abs(y2 - y1), sy = (y1 < y2) ? 1 : -1;
	int err = dx + dy;

	while (true) {
		if (
			string& object = (*map)[0][y1][x1];

			(object != DOOR) &&
			(object != TB_WALL) &&
			(object != SIDE_WALL) &&
			(object != TL_WALL) &&
			(object != TR_WALL) &&
			(object != BL_WALL) &&
			(object != BR_WALL)
			) {

			object = HALL;
		}
		if (x1 == x2 &&
			y1 == y2)		break;
		int e2 = 2 * err;
		if (e2 >= dy) { err += dy; x1 += sx; }
		if (e2 <= dx) { err += dx; y1 += sy; }
	}
}

void generateTown(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, vector<Enemy*>& enemies) {
	player.stage = "TOWN";

	if (player.sublevel == 0) {
		generateRoom(map, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, 26, 7);

		(*map)[0][10][31] = SHOP;
		(*map)[0][11][47] = ENTERANCE;

		player.x = 38;
		player.y = 9;
		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		player.sublevel += 1;
	}
	else {
		player.sublevel = 1;
		loadLevel(map, player, enemies, "SEWER");
	}
}

void generateSewer(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, vector<Enemy*>& enemies) {
	player.stage = "SEWER";

	int sublevel = player.sublevel;

	if (sublevel == 1) {
		{
			// TL
			generateRoom(map, 4, 4, 0, 0, { {2, 3} });
			generateEnemies(map, enemies, player.stage, 4, 4, 0, 0);
			generateItems(map, 4, 4, 0, 0);

			// TR
			generateRoom(map, 8, 6, 43, 0, { {43, 2}, {47, 5} });
			generateEnemies(map, enemies, player.stage, 8, 6, 43, 0);
			generateItems(map, 8, 6, 43, 0);

			// M
			generateRoom(map, 9, 6, 8, 7, { {16, 10}, { 8, 11 }, {10, 12} });
			generateEnemies(map, enemies, player.stage, 9, 6, 8, 7);
			generateItems(map, 9, 6, 8, 7);

			// B
			generateRoom(map, 4, 4, 38, 16, { {38, 17}, {41, 17} });
			generateEnemies(map, enemies, player.stage, 4, 4, 38, 16);
			generateItems(map, 4, 4, 38, 16);

		}

		{
			// TL to ML
			generateHall(map, 2, 4, 4, 5);
			generateHall(map, 4, 5, 5, 8);
			generateHall(map, 5, 8, 7, 11);
			generateHall(map, 3, 4, 6, 11);

			// TR to B
			generateHall(map, 47, 6, 46, 8);
			generateHall(map, 46, 8, 45, 10);
			generateHall(map, 45, 10, 48, 11);
			generateHall(map, 48, 11, 42, 14);
			generateHall(map, 42, 14, 42, 17);
			generateHall(map, 45, 8, 47, 7);

			// M to TL
			generateHall(map, 17, 10, 27, 6);
			generateHall(map, 27, 6, 42, 2);
			generateHall(map, 18, 9, 26, 6);
			generateHall(map, 29, 6, 43, 2);

			// M to B
			generateHall(map, 10, 13, 15, 14);
			generateHall(map, 15, 14, 27, 14);
			generateHall(map, 27, 14, 34, 15);
			generateHall(map, 34, 15, 37, 17);
			generateHall(map, 31, 14, 36, 17);
			generateHall(map, 9, 13, 12, 14);
			generateHall(map, 12, 13, 12, 13);

			// Middle pass-through
			generateHall(map, 25, 7, 31, 14);
			generateHall(map, 25, 8, 30, 14);


			// Rightmost dead-end
			generateHall(map, 44, 12, 64, 3);
			generateHall(map, 44, 13, 65, 3);
			generateHall(map, 43, 13, 43, 13);

			// Leftmost dead-end
			generateHall(map, 9, 13, 6, 17);
			generateHall(map, 10, 13, 5, 17);

			// Right branch
			generateHall(map, 7, 16, 21, 18);
			generateHall(map, 10, 17, 18, 17);
		}


		(*map)[0][18][40] = SIGN;
		(*map)[0][8][14] = ENTERANCE;


		player.x = 39;
		player.y = 17;

		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		message("You enter the sewer, domain of sludge and filth.");
		message("It is dark, damp, and full of danger.");

		player.sublevel += 1;
	}
	elif(sublevel == 2) {
		{
			// TL
			generateRoom(map, 22, 4, 2, 1, { {2, 2}, {4, 4}, {22, 4} });
			generateEnemies(map, enemies, player.stage, 22, 4, 2, 1);
			generateItems(map, 22, 4, 2, 1);

			// TM
			generateRoom(map, 7, 4, 26, 0, { {28, 3} });
			generateEnemies(map, enemies, player.stage, 7, 4, 26, 0);
			generateItems(map, 7, 4, 26, 0);

			// TR
			generateRoom(map, 13, 4, 64, 0, { {64, 2}, {73, 3} });
			generateEnemies(map, enemies, player.stage, 13, 4, 64, 0);
			generateItems(map, 13, 4, 64, 0);

			// ML
			generateRoom(map, 4, 6, 10, 7, { {10, 9}, {13, 9} });
			generateEnemies(map, enemies, player.stage, 4, 6, 10, 7);
			generateItems(map, 4, 6, 10, 7);

			// MM
			generateRoom(map, 4, 6, 46, 7, { {46, 10} });
			generateEnemies(map, enemies, player.stage, 4, 6, 46, 7);
			generateItems(map, 4, 6, 46, 7);

			// MR
			generateRoom(map, 17, 4, 52, 7, { {59, 7} });
			generateEnemies(map, enemies, player.stage, 17, 4, 52, 7);
			generateItems(map, 17, 4, 52, 7);

			// BL
			generateRoom(map, 5, 6, 20, 14, { {20, 16}, {23, 14} });
			generateEnemies(map, enemies, player.stage, 5, 6, 20, 14);
			generateItems(map, 5, 6, 20, 14);

			// BM
			generateRoom(map, 25, 4, 26, 16, { {36, 16}, {50, 18} });
			generateEnemies(map, enemies, player.stage, 25, 4, 26, 16);
			generateItems(map, 25, 4, 26, 16);
		}

		{
			// TM to MM
			generateHall(map, 28, 4, 45, 10);
			generateHall(map, 30, 4, 43, 9);
			generateHall(map, 43, 10, 43, 10);

			// TR to BM
			generateHall(map, 51, 18, 73, 13);
			generateHall(map, 73, 13, 73, 4);
			generateHall(map, 54, 18, 72, 14);

			// TR to MR
			generateHall(map, 63, 2, 60, 3);
			generateHall(map, 60, 3, 59, 6);
			generateHall(map, 61, 2, 59, 4);

			// TL to ML
			generateHall(map, 4, 5, 9, 9);
			generateHall(map, 4, 6, 8, 9);

			generateHall(map, 22, 5, 19, 7);
			generateHall(map, 19, 7, 14, 9);
			generateHall(map, 22, 6, 15, 9);

			// BL to hall
			generateHall(map, 32, 6, 26, 8);
			generateHall(map, 31, 7, 27, 8);
			generateHall(map, 26, 9, 23, 13);
			generateHall(map, 26, 10, 24, 13);

			// BM to hall between TL MM
			generateHall(map, 39, 8, 38, 12);
			generateHall(map, 37, 12, 36, 15);
			generateHall(map, 38, 10, 37, 14);
			generateHall(map, 39, 10, 39, 10);

			// Left side amalgamation
			generateHall(map, 1, 2, 0, 5);
			generateHall(map, 0, 6, 5, 19);
			generateHall(map, 1, 10, 3, 15);
			generateHall(map, 6, 8, 4, 15);
			generateHall(map, 7, 9, 3, 12);

			generateHall(map, 0, 3, 0, 3);
			generateHall(map, 0, 8, 0, 8);
			generateHall(map, 3, 11, 3, 11);

			generateHall(map, 5, 14, 5, 17);

			generateHall(map, 19, 16, 5, 18);
			generateHall(map, 17, 16, 7, 18);
		}

		(*map)[0][2][29] = ENTERANCE;


		player.x = 11;
		player.y = 8;

		drawRoom(map, player.x, player.y);

		(*map)[0][player.y][player.x] = PLAYER;

		player.sublevel += 1;
	}
	elif(sublevel == 3) {
		{
			// TM
			generateRoom(map, 5, 6, 36, 0, { {38, 5} });
			generateEnemies(map, enemies, player.stage, 5, 6, 36, 0);
			generateItems(map, 5, 6, 36, 0);

			// ML
			generateRoom(map, 6, 6, 8, 7, { {11, 12} });
			generateEnemies(map, enemies, player.stage, 6, 6, 8, 7);
			generateItems(map, 6, 6, 8, 7);

			// MM
			generateRoom(map, 15, 6, 31, 7, { {38, 12}, {38, 7} });
			generateEnemies(map, enemies, player.stage, 15, 6, 31, 7);
			generateBoss(map, enemies, player.stage, 15, 6, 31, 7);
			generateItems(map, 15, 6, 31, 7);

			// BM
			generateRoom(map, 5, 6, 36, 14, { {36, 18}, {38, 14} });
			generateEnemies(map, enemies, player.stage, 5, 6, 36, 14);
			generateItems(map, 5, 6, 36, 14);
		}

		{
			// ML to BM
			generateHall(map, 11, 13, 12, 16);
			generateHall(map, 12, 16, 15, 17);
			generateHall(map, 15, 17, 18, 18);
			generateHall(map, 18, 18, 35, 18);
			generateHall(map, 11, 15, 14, 16);
			generateHall(map, 17, 17, 17, 17);

			// BM to MM
			generateHall(map, 38, 13, 38, 13);

			// MM to TM
			generateHall(map, 38, 6, 38, 6);
		}

		(*map)[0][2][38] = ENTERANCE;

		player.x = 10;
		player.y = 9;

		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		player.sublevel += 1;
	}
	else {
		player.sublevel = 1;
		loadLevel(map, player, enemies, "CAVE");
	}
}

void generateCave(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, vector<Enemy*>& enemies) {
	player.stage = "CAVE";

	int sublevel = player.sublevel;

	if (sublevel == 1) {
		{
			// TL
			generateRoom(map, 16, 6, 7, 0, { {16, 5} });
			generateEnemies(map, enemies, player.stage, 16, 6, 7, 0);
			generateItems(map, 16, 6, 7, 0);

			// TM
			generateRoom(map, 13, 4, 36, 1, { {36, 3} });
			generateEnemies(map, enemies, player.stage, 13, 4, 36, 1);
			generateItems(map, 13, 4, 36, 1);

			// ML
			generateRoom(map, 4, 5, 21, 8, { {23, 12} });
			generateEnemies(map, enemies, player.stage, 4, 5, 21, 8);
			generateItems(map, 4, 5, 21, 8);

			// MM
			generateRoom(map, 11, 6, 34, 7, { {44, 9} });
			generateEnemies(map, enemies, player.stage, 11, 6, 34, 7);
			generateItems(map, 11, 6, 34, 7);

			// BL
			generateRoom(map, 7, 6, 2, 14, { {6, 14} });
			generateEnemies(map, enemies, player.stage, 7, 6, 2, 14);
			generateItems(map, 7, 6, 2, 14);

			// BM
			generateRoom(map, 5, 4, 46, 16, { {46, 18}, {49, 16} });
			generateEnemies(map, enemies, player.stage, 5, 4, 46, 16);
			generateItems(map, 5, 4, 46, 16);
		}

		{
			// TL to BL
			generateHall(map, 16, 6, 6, 13);
			generateHall(map, 15, 6, 6, 12);
			generateHall(map, 17, 6, 7, 13);


			// ML to BM
			generateHall(map, 23, 13, 28, 16);
			generateHall(map, 28, 16, 39, 18);
			generateHall(map, 39, 18, 45, 18);
			generateHall(map, 24, 13, 34, 16);
			generateHall(map, 36, 17, 45, 18);
			generateHall(map, 29, 14, 42, 16);

			// BM to MM
			generateHall(map, 48, 15, 51, 14);
			generateHall(map, 51, 14, 52, 10);
			generateHall(map, 52, 10, 51, 8);
			generateHall(map, 51, 8, 45, 9);
			generateHall(map, 52, 13, 50, 8);
			generateHall(map, 50, 9, 45, 10);
			generateHall(map, 49, 14, 49, 14);
			generateHall(map, 48, 15, 51, 14);
			generateHall(map, 51, 14, 52, 10);
			generateHall(map, 52, 10, 51, 8);
			generateHall(map, 51, 8, 45, 9);
			generateHall(map, 52, 13, 50, 8);
			generateHall(map, 50, 9, 45, 10);
			generateHall(map, 49, 14, 49, 14);


			// TM to hall
			generateHall(map, 35, 3, 30, 4);
			generateHall(map, 30, 4, 28, 10);
			generateHall(map, 28, 10, 28, 13);
			generateHall(map, 35, 2, 28, 8);

			// Left side connections
			generateHall(map, 29, 17, 26, 19);
			generateHall(map, 26, 18, 22, 19);
			generateHall(map, 21, 19, 18, 17);

			generateHall(map, 19, 17, 21, 14);
			generateHall(map, 21, 14, 15, 14);
			generateHall(map, 15, 14, 17, 10);
			generateHall(map, 18, 10, 17, 7);
			generateHall(map, 17, 7, 14, 7);
			generateHall(map, 16, 11, 13, 10);
			generateHall(map, 15, 12, 12, 10);

			generateHall(map, 19, 15, 18, 17);
			generateHall(map, 18, 17, 11, 16);
			generateHall(map, 11, 16, 9, 11);
			generateHall(map, 10, 12, 12, 16);
			generateHall(map, 15, 16, 10, 19);
			generateHall(map, 10, 18, 13, 17);

			generateHall(map, 21, 18, 21, 18);
			generateHall(map, 24, 18, 24, 18);
			generateHall(map, 29, 18, 29, 18);

			// Right side dead ends
			generateHall(map, 52, 10, 55, 6);
			generateHall(map, 56, 6, 58, 4);
			generateHall(map, 58, 4, 68, 3);
			generateHall(map, 54, 9, 58, 3);
			generateHall(map, 56, 7, 58, 5);
			generateHall(map, 53, 10, 53, 10);
			generateHall(map, 63, 4, 63, 4);
		}


		(*map)[0][1][16] = ENTERANCE;

		player.x = 37;
		player.y = 9;

		drawRoom(map, player.x, player.y);

		(*map)[0][player.y][player.x] = PLAYER;

		message("You are now entering a cave, home to the slimy and the dank.");
		message("It is a dark place filled to the brim with creepy crawlies and an impending sense of dread");

		player.sublevel += 1;
	}
	elif(sublevel == 2) {
		{
			// TL
			generateRoom(map, 5, 4, 16, 1, { {19, 4} });
			generateEnemies(map, enemies, player.stage, 5, 4, 16, 1);
			generateItems(map, 5, 4, 16, 1);

			// TM
			generateRoom(map, 9, 6, 27, 0, { {35, 2} });
			generateEnemies(map, enemies, player.stage, 9, 6, 27, 0);
			generateItems(map, 9, 6, 27, 0);

			// ML
			generateRoom(map, 9, 4, 4, 8, { {7, 8}, { 12, 9 }, {6, 11} });
			generateEnemies(map, enemies, player.stage, 9, 4, 4, 8);
			generateItems(map, 9, 4, 4, 8);

			// MR
			generateRoom(map, 5, 5, 60, 8, { {62, 8}, { 60, 11 } });
			generateEnemies(map, enemies, player.stage, 5, 5, 60, 8);
			generateItems(map, 5, 5, 60, 8);

			// BL
			generateRoom(map, 6, 5, 10, 15, { {13, 15}, {15, 17} });
			generateEnemies(map, enemies, player.stage, 6, 5, 10, 15);
			generateItems(map, 6, 5, 10, 15);

			// BR
			generateRoom(map, 15, 5, 55, 14, { {55, 17} });
			generateEnemies(map, enemies, player.stage, 15, 5, 55, 14);
			generateItems(map, 15, 5, 55, 14);

		}


		{
			// TL to BR
			generateHall(map, 19, 5, 23, 9);
			generateHall(map, 23, 9, 28, 11);
			generateHall(map, 28, 11, 32, 13);
			generateHall(map, 32, 13, 42, 16);
			generateHall(map, 42, 16, 54, 17);
			generateHall(map, 19, 6, 20, 7);
			generateHall(map, 22, 7, 24, 10);
			generateHall(map, 29, 11, 33, 14);
			generateHall(map, 31, 12, 31, 12);
			generateHall(map, 34, 15, 45, 17);
			generateHall(map, 48, 16, 48, 16);


			// TM to MR
			generateHall(map, 36, 2, 49, 3);
			generateHall(map, 49, 3, 51, 7);
			generateHall(map, 51, 7, 54, 9);
			generateHall(map, 55, 10, 59, 11);
			generateHall(map, 42, 3, 52, 7);
			generateHall(map, 48, 4, 48, 4);
			generateHall(map, 53, 9, 56, 11);


			// ML to BL
			generateHall(map, 13, 9, 15, 10);
			generateHall(map, 15, 10, 15, 13);
			generateHall(map, 15, 13, 13, 14);
			generateHall(map, 14, 9, 14, 9);
			generateHall(map, 14, 13, 14, 13);

			// BL to Middle Hall
			generateHall(map, 16, 17, 22, 16);
			generateHall(map, 22, 16, 26, 11);
			generateHall(map, 19, 17, 26, 12);
			generateHall(map, 20, 17, 25, 11);


			// TM MM BM Hall Connection
			generateHall(map, 50, 5, 46, 5);
			generateHall(map, 46, 5, 43, 8);
			generateHall(map, 43, 8, 42, 16);
			generateHall(map, 42, 11, 46, 6);

			// ML to TL Dead End
			generateHall(map, 7, 7, 6, 5);
			generateHall(map, 6, 5, 3, 4);
			generateHall(map, 3, 3, 4, 2);
			generateHall(map, 4, 2, 11, 3);
			generateHall(map, 11, 3, 11, 0);
			generateHall(map, 7, 6, 4, 5);
			generateHall(map, 4, 3, 9, 2);

			// ML to BL Dead End
			generateHall(map, 7, 12, 4, 13);
			generateHall(map, 3, 14, 5, 19);
			generateHall(map, 6, 13, 4, 14);
			generateHall(map, 3, 16, 5, 17);

			// MR to TR Dead End
			generateHall(map, 62, 7, 64, 4);
			generateHall(map, 64, 5, 68, 2);
			generateHall(map, 69, 2, 73, 0);
			generateHall(map, 62, 6, 69, 2);
			generateHall(map, 64, 6, 67, 2);
			generateHall(map, 69, 1, 71, 0);
			generateHall(map, 71, 2, 73, 1);
		}

		(*map)[0][2][29] = ENTERANCE;

		player.x = 58;
		player.y = 16;

		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		player.sublevel += 1;
	}
	elif(sublevel == 3) {
		{
			generateRoom(map, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, 26, 7, { {50, 9} });
			generateEnemies(map, enemies, player.stage, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, 26, 7);
			generateBoss(map, enemies, player.stage, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, 26, 7);
			generateItems(map, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, 26, 7);

			generateRoom(map, 6, 6, 60, 7, { {64, 7} });
			generateEnemies(map, enemies, player.stage, 6, 6, 60, 7);
			generateItems(map, 6, 6, 60, 7);
		}

		{
			generateHall(map, 51, 9, 53, 7);
			generateHall(map, 53, 7, 54, 3);
			generateHall(map, 54, 3, 61, 2);
			generateHall(map, 62, 2, 64, 6);
			generateHall(map, 52, 9, 55, 6);
			generateHall(map, 53, 5, 57, 2);
			generateHall(map, 61, 3, 64, 4);
		}

		(*map)[0][10][62] = ENTERANCE;

		player.x = 34;
		player.y = 9;

		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		player.sublevel += 1;
	}
	else {
		player.sublevel = 1;
		loadLevel(map, player, enemies, "FOREST");
	}
}

void generateForest(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, vector<Enemy*>& enemies) {
	player.stage = "FOREST";

	int sublevel = player.sublevel;

	if (sublevel == 1) {
		{
			// TL
			generateRoom(map, 7, 6, 18, 0, { {24, 3} });
			generateEnemies(map, enemies, player.stage, 7, 6, 18, 0);
			generateItems(map, 7, 6, 18, 0);

			// TR
			generateRoom(map, 4, 4, 52, 2, { {52, 4} });
			generateEnemies(map, enemies, player.stage, 4, 4, 52, 2);
			generateItems(map, 4, 4, 52, 2);

			// BL
			generateRoom(map, 7, 4, 12, 15, { {18, 16} });
			generateEnemies(map, enemies, player.stage, 7, 4, 12, 15);
			generateItems(map, 7, 4, 12, 15);
		}

		// This whole thing is an amalgamation (see map Forest 1), there will be no specific room-to-room connections
		{
			generateHall(map, 2, 19, 9, 11);
			generateHall(map, 3, 17, 3, 17);
			generateHall(map, 3, 19, 6, 12);
			generateHall(map, 7, 14, 11, 10);
			generateHall(map, 11, 9, 8, 8);
			generateHall(map, 11, 11, 10, 8);
			generateHall(map, 8, 7, 11, 4);
			generateHall(map, 8, 6, 11, 3);
			generateHall(map, 11, 2, 10, 0);
			generateHall(map, 11, 1, 11, 1);

			generateHall(map, 12, 10, 33, 11);
			generateHall(map, 23, 10, 25, 13);
			generateHall(map, 27, 10, 41, 11);

			generateHall(map, 19, 16, 23, 15);
			generateHall(map, 23, 15, 24, 13);
			generateHall(map, 23, 14, 23, 14);

			generateHall(map, 21, 16, 24, 18);
			generateHall(map, 22, 16, 25, 18);
			generateHall(map, 26, 18, 35, 16);
			generateHall(map, 26, 17, 33, 16);

			generateHall(map, 26, 13, 31, 14);
			generateHall(map, 31, 14, 34, 12);
			generateHall(map, 26, 14, 34, 13);

			generateHall(map, 25, 3, 28, 2);
			generateHall(map, 26, 2, 26, 2);
			generateHall(map, 28, 2, 32, 4);
			generateHall(map, 29, 2, 31, 3);
			generateHall(map, 32, 5, 33, 7);
			generateHall(map, 33, 5, 35, 11);
			generateHall(map, 33, 9, 33, 9);

			generateHall(map, 43, 0, 40, 5);
			generateHall(map, 43, 1, 42, 3);
			generateHall(map, 40, 4, 39, 7);
			generateHall(map, 38, 8, 40, 10);
			generateHall(map, 38, 7, 39, 10);
			generateHall(map, 40, 6, 38, 9);

			generateHall(map, 51, 4, 49, 5);
			generateHall(map, 50, 4, 49, 7);
			generateHall(map, 48, 6, 46, 7);
			generateHall(map, 46, 7, 45, 14);
			generateHall(map, 45, 10, 46, 13);

			generateHall(map, 48, 7, 55, 12);
			generateHall(map, 54, 12, 56, 15);
			generateHall(map, 51, 8, 52, 13);

			generateHall(map, 62, 7, 58, 14);
			generateHall(map, 62, 8, 58, 13);
			generateHall(map, 62, 9, 58, 12);
			generateHall(map, 56, 14, 58, 15);

			generateHall(map, 46, 14, 56, 16);
			generateHall(map, 46, 15, 51, 16);

			// BM Circle
			generateHall(map, 39, 12, 44, 13);
			generateHall(map, 42, 12, 44, 14);
			generateHall(map, 44, 15, 41, 18);
			generateHall(map, 44, 16, 42, 18);
			generateHall(map, 40, 18, 36, 17);
			generateHall(map, 38, 18, 37, 15);
			generateHall(map, 37, 14, 39, 13);
		}

		(*map)[0][3][54] = ENTERANCE;

		player.x = 14;
		player.y = 16;

		drawRoom(map, player.x, player.y);

		(*map)[0][player.y][player.x] = PLAYER;

		message("You enter the forest, realm of the whimsical and the spooky.");

		player.sublevel += 1;
	}
	elif(sublevel == 2) {
		{
			// TL
			generateRoom(map, 6, 6, 12, 0, { {14, 5} });
			generateEnemies(map, enemies, player.stage, 6, 6, 12, 0);
			generateItems(map, 6, 6, 12, 0);

			// BL
			generateRoom(map, 6, 5, 10, 15, { {13, 15} });
			generateEnemies(map, enemies, player.stage, 6, 5, 10, 15);
			generateItems(map, 6, 5, 10, 15);

			// BR
			generateRoom(map, 6, 6, 59, 14, { {62, 14} });
			generateEnemies(map, enemies, player.stage, 6, 6, 59, 14);
			generateItems(map, 6, 6, 59, 14);

		}

		{
			// Circle
			generateHall(map, 37, 3, 42, 4);
			generateHall(map, 39, 3, 34, 4);
			generateHall(map, 36, 3, 40, 3);

			generateHall(map, 43, 5, 44, 10);
			generateHall(map, 44, 9, 43, 14);
			generateHall(map, 44, 7, 44, 12);

			generateHall(map, 37, 16, 42, 15);
			generateHall(map, 39, 16, 34, 15);
			generateHall(map, 36, 16, 40, 16);

			generateHall(map, 33, 5, 32, 10);
			generateHall(map, 32, 9, 33, 14);
			generateHall(map, 32, 7, 32, 12);

			generateHall(map, 34, 5, 34, 5);
			generateHall(map, 42, 5, 42, 5);
			generateHall(map, 42, 14, 42, 14);
			generateHall(map, 34, 14, 34, 14);

			// Circle Inner Pathways
			generateHall(map, 38, 2, 38, 18);
			generateHall(map, 26, 9, 61, 9);
			generateHall(map, 28, 10, 46, 10);

			// Circle TM to TR Dead End
			generateHall(map, 38, 2, 55, 1);
			generateHall(map, 47, 2, 56, 1);
			generateHall(map, 52, 2, 57, 0);

			// Circle MM to TL Dead End
			generateHall(map, 47, 8, 58, 7);
			generateHall(map, 53, 8, 58, 8);
			generateHall(map, 59, 7, 59, 7);
			generateHall(map, 59, 6, 64, 5);
			generateHall(map, 61, 5, 68, 6);
			generateHall(map, 64, 6, 69, 5);

			// BR Room Connection
			generateHall(map, 58, 10, 63, 12);
			generateHall(map, 60, 10, 63, 11);
			generateHall(map, 62, 13, 63, 13);
			generateHall(map, 62, 10, 52, 10);

			// Circle to BR Dead End
			generateHall(map, 43, 13, 54, 14);
			generateHall(map, 49, 13, 54, 15);
			generateHall(map, 51, 13, 51, 13);
			generateHall(map, 52, 13, 55, 18);
			generateHall(map, 53, 13, 55, 18);
			generateHall(map, 55, 19, 50, 18);
			generateHall(map, 52, 19, 52, 19);

			// Circle to BL Dead End
			generateHall(map, 38, 18, 29, 17);
			generateHall(map, 33, 18, 28, 16);
			generateHall(map, 27, 16, 20, 19);
			generateHall(map, 25, 16, 18, 19);

			// Circle to TL Dead End (and BL Room Connection)
			generateHall(map, 33, 13, 12, 12);
			generateHall(map, 22, 13, 13, 14);
			generateHall(map, 16, 13, 16, 13);
			generateHall(map, 12, 13, 5, 14);
			generateHall(map, 8, 13, 9, 14);
			generateHall(map, 6, 14, 5, 9);
			generateHall(map, 5, 8, 10, 6);
			generateHall(map, 6, 7, 9, 6);
			generateHall(map, 9, 6, 9, 0);
			generateHall(map, 5, 12, 5, 12);
			generateHall(map, 12, 14, 12, 14);

			// Circle to TL Room
			generateHall(map, 28, 11, 19, 9);
			generateHall(map, 25, 11, 16, 10);
			generateHall(map, 16, 9, 14, 6);
			generateHall(map, 15, 9, 14, 7);
			generateHall(map, 22, 9, 22, 9);

			// Circle to TM Dead End
			generateHall(map, 27, 9, 24, 8);
			generateHall(map, 26, 8, 24, 7);
			generateHall(map, 23, 6, 26, 1);
			generateHall(map, 23, 5, 24, 2);
			generateHall(map, 26, 2, 28, 0);
			generateHall(map, 27, 0, 27, 0);
			generateHall(map, 23, 7, 23, 7);
		}

		(*map)[0][17][62] = ENTERANCE;

		player.x = 15;
		player.y = 2;

		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		player.sublevel += 1;
	}
	elif(sublevel == 3) {
		{
			// MM
			generateRoom(map, 14, 6, 34, 7, { {34, 9}, {47, 10} });
			generateEnemies(map, enemies, player.stage, 14, 6, 34, 7);
			generateItems(map, 14, 6, 34, 7);

			generateRoom(map, 12, 4, 13, 14, { {19, 14} });
			generateEnemies(map, enemies, player.stage, 12, 4, 13, 14);
			generateItems(map, 12, 4, 13, 14);

			// BR
			generateRoom(map, 6, 6, 59, 14, { {62, 14} });
			generateEnemies(map, enemies, player.stage, 6, 6, 59, 14);
			generateItems(map, 6, 6, 59, 14);

		}

		{
			// BR to MM
			generateHall(map, 62, 13, 59, 11);
			generateHall(map, 62, 12, 57, 10);
			generateHall(map, 59, 11, 54, 10);
			generateHall(map, 54, 9, 48, 9);
			generateHall(map, 54, 10, 48, 10);

			// BL to MM
			generateHall(map, 19, 13, 22, 11);
			generateHall(map, 19, 12, 22, 10);
			generateHall(map, 22, 10, 27, 10);
			generateHall(map, 28, 10, 33, 10);
			generateHall(map, 28, 9, 33, 9);
		}

		(*map)[0][15][16] = ENTERANCE;

		player.x = 63;
		player.y = 17;

		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		player.sublevel += 1;
	}
	else {
		player.sublevel = 1;
		loadLevel(map, player, enemies, "CASTLE");
	}
}

void generateCastle(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, vector<Enemy*>& enemies) {
	player.stage = "CASTLE";

	int sublevel = player.sublevel;

	if (sublevel == 1) {
		{
			// TM
			generateRoom(map, 4, 4, 27, 0, { {27, 2}, {28, 3} });
			generateEnemies(map, enemies, player.stage, 4, 4, 27, 0);
			generateItems(map, 4, 4, 27, 0);

			// ML
			generateRoom(map, 5, 6, 9, 7, { {12, 7}, {13, 9} });
			generateEnemies(map, enemies, player.stage, 5, 6, 9, 7);
			generateItems(map, 5, 6, 9, 7);

			// MM
			generateRoom(map, 9, 5, 36, 7, { {36, 9}, {44, 9}, {40, 11} });
			generateEnemies(map, enemies, player.stage, 9, 5, 36, 7);
			generateItems(map, 9, 5, 36, 7);

			// MR
			generateRoom(map, 7, 6, 60, 7, { {60, 9} });
			generateEnemies(map, enemies, player.stage, 7, 6, 60, 7);
			generateItems(map, 7, 6, 60, 7);

			// BM
			generateRoom(map, 5, 5, 31, 15, { {35, 17} });
			generateEnemies(map, enemies, player.stage, 5, 5, 31, 15);
			generateItems(map, 5, 5, 31, 15);
		}

		{
			// TM to ML
			generateHall(map, 26, 2, 12, 2);
			generateHall(map, 12, 2, 12, 6);

			// TM to ML-MM
			generateHall(map, 28, 4, 28, 9);

			// ML to MM
			generateHall(map, 14, 9, 35, 9);

			// MM to MR
			generateHall(map, 45, 9, 59, 9);

			// MM to BM
			generateHall(map, 40, 12, 40, 17);

			// BL to T dead end
			generateHall(map, 36, 17, 51, 17);
			generateHall(map, 51, 17, 51, 0);
		}

		(*map)[0][1][29] = ENTERANCE;

		player.x = 63;
		player.y = 10;

		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		message("You enter the castle.");
		message("It is a cold place, and all the curtains are drawn tightly shut");

		player.sublevel += 1;
	}
	elif(sublevel == 2) {
		{
			// TM
			generateRoom(map, 11, 6, 32, 0, { {38, 5} });
			generateEnemies(map, enemies, player.stage, 11, 6, 32, 0);
			generateItems(map, 11, 6, 32, 0);

			// ML
			generateRoom(map, 6, 5, 3, 7, { {8, 9} });
			generateEnemies(map, enemies, player.stage, 6, 5, 3, 7);
			generateItems(map, 6, 5, 3, 7);

			// BM
			generateRoom(map, 15, 6, 33, 14, { {38, 14}, {47, 16} });
			generateEnemies(map, enemies, player.stage, 15, 6, 33, 14);
			generateItems(map, 15, 6, 33, 14 );

			// BR
			generateRoom(map, 6, 6, 62, 14, { {65, 14}, {62, 16} });
			generateEnemies(map, enemies, player.stage, 6, 6, 62, 14);
			generateItems(map, 6, 6, 62, 14);
		}

		{
			// TM to BM
			generateHall(map, 38, 6, 38, 13);

			// ML to BR
			generateHall(map, 9, 9, 65, 9);
			generateHall(map, 65, 9, 65, 13);

			// BM to BR
			generateHall(map, 48, 16, 61, 16);
		}

		(*map)[0][16][41] = ENTERANCE;

		player.x = 5;
		player.y = 9;

		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		player.sublevel += 1;
	}
	elif(sublevel == 3) {
		{
			// ML
			generateRoom(map, 25, 6, 0, 7, { {24, 10} });
			generateEnemies(map, enemies, player.stage, 25, 6, 0, 7);
			generateBoss(map, enemies, player.stage, 25, 6, 0, 7);
			generateItems(map, 25, 6, 0, 7);

			// MM
			generateRoom(map, 9, 6, 33, 7, { {33, 10}, {37, 12} });
			generateEnemies(map, enemies, player.stage, 9, 6, 33, 7);
			generateItems(map, 9, 6, 33, 7);

			// BM
			generateRoom(map, 4, 4, 35, 16, { {37, 16} });
			generateEnemies(map, enemies, player.stage, 4, 4, 35, 16);
			generateItems(map, 4, 4, 35, 16);
		}

		{
			// ML to MM
			generateHall(map, 25, 10, 32, 10);

			// MM to BM
			generateHall(map, 37, 13, 37, 15);
		}

		(*map)[0][8][1] = ENTERANCE;

		player.x = 36;
		player.y = 18;
		(*map)[0][player.y][player.x] = PLAYER;

		drawRoom(map, player.x, player.y);

		player.sublevel += 1;
	}
	else {
		winMenu(player);
	}
}
