/*
Dustin Bellina

I tried to implement procedural dungeon generation for replayability but that is absolutely not happening in the given timeframe.
The map generation works roughly how Rogue works:
	1. Split the map area into 9 subsections and place one room max randomly in each.
	2. Place the objects that absolutely need to be there (exits, signs, shop, etc.)
	3. Randomly place any other items (Not implemented)
	4. Spawn enemies (Not implemented)

Functions:
	clearScreen(): clears the screen
	generateRoom(): generates a room of specified parameters
	generateTown(): generates the town
*/

#include <iostream>
#include <string>

#include "defs.h"
#include "prototypes.h"


using namespace std;


void clearScreen();
void drawMap(string(*map)[MAP_HEIGHT][MAP_WIDTH]);
void generateRoom(string(*map)[MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY);
void generateTown(string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2]);


void clearScreen() {
	cout << "\033[2J\033[1;1H";
}

void generateRoom(string(*map)[MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY) {
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
}

void generateTown(string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			(*map)[i][j] = " ";
		}
	}

	generateRoom(map, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, 26, 7);

	(*map)[10][31] = SHOP;
	(*map)[11][47] = SEWER_ENTERANCE;
	(*map)[9][38] = PLAYER;

	(*playerXY)[0] = 38;
	(*playerXY)[1] = 9;

	drawMap(map);
}

void drawMap(string(*map)[MAP_HEIGHT][MAP_WIDTH]) {
	clearScreen();

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			cout << (*map)[i][j];
		}
		cout << "\n";
	}
}


//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//.........................▒╔═══════════════════════╗▒.........................
//.........................▒║.......................║▒.........................
//.........................▒║...........@...........║▒.........................
//.........................▒║....⌂..................║▒.........................
//.........................▒║....................☼..║▒.........................
//.........................▒╚═══════════════════════╝▒.........................
//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
//.........................▒.........................▒.........................
