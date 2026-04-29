/*
Dustin Bellina

Functions:
	clearScreen(): clears the screen
	drawMap(): Displays the map
	clearMap(): Clears the map array **Does not display the cleared map**
	generateRoom(): Generates a room of specified parameters
	generateHall(): Uses Bresenham's line algorithm to generate hallways in the map

	generateTown()
	generateSewer()
*/

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "prototypes.h"


using namespace std;

void clearScreen() {
	cout << CURSOR_HOME;
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		cout << CLEAR_LINE << "\033[1B" << flush;
	}
	cout << CURSOR_HOME;
}

void drawMap(string(*map)[MAP_HEIGHT][MAP_WIDTH], string object) {
	clearScreen();

	string mapCell;

	cout << "\n";	// Reserve the top line for text

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			mapCell = (*map)[i][j];

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
		cout << "\n";
	}
}

void clearMap(string(*map)[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			(*map)[i][j] = " ";
		}
	}
}

void generateRoom(string(*map)[MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY, vector<pair<int, int>> doors) {
	for (int i = 0; i < rH; i++) {
		for (int j = 0; j < rW; j++) {
			bool top = (i == 0);
			bool bottom = (i == rH - 1);
			bool left = (j == 0);
			bool right = (j == rW - 1);

			if (top && left)		(*map)[i + rY][j + rX] = TL_WALL;
			elif(top && right)		(*map)[i + rY][j + rX] = TR_WALL;
			elif(bottom && left)	(*map)[i + rY][j + rX] = BL_WALL;
			elif(bottom && right)	(*map)[i + rY][j + rX] = BR_WALL;
			elif(top || bottom)		(*map)[i + rY][j + rX] = TB_WALL;
			elif(left || right)		(*map)[i + rY][j + rX] = SIDE_WALL;
			else                    (*map)[i + rY][j + rX] = FLOOR;
		}
	}

	for (auto &door : doors)
		(*map)[door.second][door.first] = DOOR;
}

// Implementation of Bresenham's line algorithm: https://gist.github.com/ssavi-ict/092501c69e2ffec65e96a8865470ad2f enhanced for this purpose by ai
void generateHall(string(*map)[MAP_HEIGHT][MAP_WIDTH], int x1, int y1, int x2, int y2) {
	int dx = abs(x2 - x1), sx = (x1 < x2) ? 1 : -1;
	int dy = -abs(y2 - y1), sy = (y1 < y2) ? 1 : -1;
	int err = dx + dy;

	while (true) {
		if (
			string &object = (*map)[y1][x1];

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
		if (x1 == x2 && y1 == y2)		break;
		int e2 = 2 * err;
		if (e2 >= dy) { err += dy; x1 += sx; }
		if (e2 <= dx) { err += dx; y1 += sy; }
	}
}

void generateTown(string(*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			(*map)[i][j] = " ";
		}
	}

	generateRoom(map, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, 26, 7);

	(*map)[10][31] = SHOP;
	(*map)[11][47] = SEWER_ENTERANCE;

	player.x = 38;
	player.y = 9;
	(*map)[player.y][player.x] = PLAYER;

	player.level = "TOWN";
}

void generateSewer(string(*map)[MAP_HEIGHT][MAP_WIDTH], playerType& player) {
	string level = player.level;

	if (level == "TOWN") {
		clearMap(map);

		generateRoom(map, 4, 4, 0, 0, { {2, 3} });	// Top-Left Room
		generateRoom(map, 8, 6, 43, 0, { {43, 2}, {47, 5} });	// Top-Right Room
		generateRoom(map, 9, 6, 8, 7, { {16, 10}, { 8, 11 }, {10, 12} });	// Middle Room
		generateRoom(map, 4, 4, 38, 16, { {38, 17}, {41, 17} });	// Bottom Room

		// Top-Left room to middle-left room door
		generateHall(map, 2, 4, 4, 5);
		generateHall(map, 4, 5, 5, 8);
		generateHall(map, 5, 8, 7, 11);
		generateHall(map, 3, 4, 6, 11);

		// Top-Right room to Bottom room
		generateHall(map, 47, 6, 46, 8);
		generateHall(map, 46, 8, 45, 10);
		generateHall(map, 45, 10, 48, 11);
		generateHall(map, 48, 11, 42, 14);
		generateHall(map, 42, 14, 42, 17);
		generateHall(map, 45, 8, 47, 7);

		// Middle to Top-Left room
		generateHall(map, 17, 10, 27, 6);
		generateHall(map, 27, 6, 42, 2);
		generateHall(map, 18, 9, 26, 6);
		generateHall(map, 29, 6, 43, 2);

		// Middle room to Bottom room
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


		(*map)[18][40] = SIGN;
		(*map)[8][14] = SEWER_ENTERANCE;


		player.x = 39;
		player.y = 17;

		(*map)[player.y][player.x] = PLAYER;

		player.level = "SEWER_1";
	}
}


// MAPS
/* Town
.........................▒.........................▒.........................
.........................▒.........................▒.........................
.........................▒.........................▒.........................
.........................▒.........................▒.........................
.........................▒.........................▒.........................
.........................▒.........................▒.........................
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
.........................▒╔═══════════════════════╗▒.........................
.........................▒║.......................║▒.........................
.........................▒║...........@...........║▒.........................
.........................▒║....⌂..................║▒.........................
.........................▒║....................☼..║▒.........................
.........................▒╚═══════════════════════╝▒.........................
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
.........................▒.........................▒.........................
.........................▒.........................▒.........................
.........................▒.........................▒.........................
.........................▒.........................▒.........................
.........................▒.........................▒.........................
.........................▒.........................▒.........................
*/
/* Sewer 1
╔══╗.....................|.................╔══════╗|.........................
║..║.....................|.................║......║|.........................
║..║.....................|...............▒▒╬......║|.........................
╚═╬╝.....................|...........▒▒▒▒▒.║......║|...........▒▒............
..▒......................|.........▒▒▒.....║......║|.........▒▒▒.............
..▒▒▒....................|......▒▒▒▒.......╚═══╬══╝|.......▒▒▒...............
----▒--------------------+-▒▒▒▒▒▒--------------▒---+-----▒▒▒-----------------
....▒...╔═══════╗........▒▒▒...................▒...|...▒▒▒...................
....▒▒..║.....☼.║....▒▒▒▒▒....................▒▒...|▒▒▒▒.....................
.....▒..║.......║..▒▒▒...▒▒▒..................▒...▒▒▒........................
.....▒▒.║.......╬▒▒▒.....|.▒▒................▒▒.▒▒▒|.........................
......▒▒╬.......║........|..▒▒................▒▒▒..|.........................
........╚═╬═════╝........|...▒▒.............▒▒▒....|.........................
---------▒▒▒▒▒▒▒---------+----▒▒▒-----------▒------+-------------------------
.........▒▒....▒▒▒▒▒▒▒▒▒▒▒▒▒....▒..........▒▒......|.........................
........▒▒...............|.▒▒▒▒▒▒▒▒▒......▒▒.......|.........................
......▒▒▒▒...............|........▒▒▒.╔══╗▒........|.........................
.....▒▒..▒▒▒▒▒▒▒.........|..........▒▒╬@.╬▒........|.........................
...............▒▒▒▒▒▒▒...|............║.↑║.........|.........................
.........................|............╚══╝.........|.........................
*/
