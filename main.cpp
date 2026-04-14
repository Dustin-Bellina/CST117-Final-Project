/*
Dustin Bellina

This is the behind-the-scenes system tying everything together.  I tried to implement procedural dungeon generation for replayability but that is absolutely not happening in the given timeframe.
The map works roughly how Rogue works:
	1. Split the map area into 9 subsections and place one room max randomly in each.
	2. Place the objects that absolutely need to be there (exits, signs, shop, etc.)
	3. Randomly place any other items
	4. Spawn enemies

Functions:
	clearScreen(): clears the screen
	generateRoom(): generates a room of specified parameters
	generateTown(): generates the town
	keyDetector(): detect when a key is pressed
	movemenrHandler(): handle movement

*/

#include <conio.h>	// Keyboard handling
#include <iostream>
#include <string>

#ifdef _WIN32
	#include <windows.h>	// Windows API
#endif

#include "defs.h"


using namespace std;


void clearScreen();
void drawMap(string(*map)[MAP_HEIGHT][MAP_WIDTH]);
void generateRoom(string(*map)[MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY);
void generateTown(string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2]);
void keyDetector(string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2], string object);
void movementHandler(string(*map)[MAP_HEIGHT][MAP_WIDTH], int direction, int (*playerXY)[2], string object);


void keys();


int main() {
	// Ensure Windows outputs the wall characters properly
	#ifdef _WIN32
		SetConsoleOutputCP(65001);
	#endif

	string map[MAP_HEIGHT][MAP_WIDTH];
	int playerXY[2];

	
	generateTown(&map, &playerXY);

	keyDetector(&map, &playerXY, "");

	return 0;
}


void clearScreen() {
	cout << "\033[2J\033[1;1H";
}

void generateRoom(string (*map)[MAP_HEIGHT][MAP_WIDTH], int rW, int rH, int rX, int rY) {
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

void generateTown(string (*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2]) {
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

void drawMap(string (*map)[MAP_HEIGHT][MAP_WIDTH]) {
	clearScreen();

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			cout << (*map)[i][j];
		}
		cout << "\n";
	}
}

void keyDetector(string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2], string object) {
	int ch = 0;

	while ((ch = _getch()) != 27) {	// https://stackoverflow.com/a/10473315
		if (ch == 0 || ch == 224) {	// Separate the arrow keys.  Since they output 2 ch codes, _getch() must be run twice to get their actual code
			switch (_getch()) {
				case KEY_UP:
					movementHandler(map, 1, playerXY, object);
					break;
				case KEY_LEFT:
					movementHandler(map, 2, playerXY, object);
					break;
				case KEY_RIGHT:
					movementHandler(map, 3, playerXY, object);
					break;
				case KEY_DOWN:
					movementHandler(map, 4, playerXY, object);
					break;
				default:
					exit;
			}
		}
		else {
			switch (ch) {
				case KEY_8:	// UP
					movementHandler(map, 1, playerXY, object);
					break;
				case KEY_4:	// LEFT
					movementHandler(map, 2, playerXY, object);
					break;
				case KEY_6:	// RIGHT
					movementHandler(map, 3, playerXY, object);
					break;
				case KEY_2:	// DOWN
					movementHandler(map, 4, playerXY, object);
					break;
				case KEY_7:	// NW
					movementHandler(map, 5, playerXY, object);
					break;
				case KEY_9:	// NE
					movementHandler(map, 6, playerXY, object);
					break;
				case KEY_1:	// SW
					movementHandler(map, 7, playerXY, object);
					break;
				case KEY_3:	// SE
					movementHandler(map, 8, playerXY, object);
					break;
				default:
					exit;
			}
		}
	}
}

void movementHandler(string(*map)[MAP_HEIGHT][MAP_WIDTH], int direction, int (*playerXY)[2], string object) {
	switch (direction) {
		case 1:	// Up
			if (!((*map)[(*playerXY)[1] - 1][(*playerXY)[0]] == TB_WALL)) {
				if (object != "") {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = object;
				}
				else {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = FLOOR;
				}

				object = (*map)[(*playerXY)[1] - 1][(*playerXY)[0]];
				
				(*playerXY)[1] -= 1;

				(*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
			}
			break;
		case 2:	// Left
			if (!((*map)[(*playerXY)[1]][(*playerXY)[0] - 1] == SIDE_WALL)) {
				if (object != "") {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = object;
				}
				else {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = FLOOR;
				}

				object = (*map)[(*playerXY)[1]][(*playerXY)[0] - 1];
				
				(*playerXY)[0] -= 1;

				(*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
			}
			break;
		case 3:	// Right
			if (!((*map)[(*playerXY)[1]][(*playerXY)[0] + 1] == SIDE_WALL)) {
				if (object != "") {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = object;
				}
				else {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = FLOOR;
				}

				object = (*map)[(*playerXY)[1]][(*playerXY)[0] + 1];

				(*playerXY)[0] += 1;

				(*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
			}
			break;
		case 4:	// Down
			if (!((*map)[(*playerXY)[1] + 1][(*playerXY)[0]] == TB_WALL)) {
				if (object != "") {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = object;
				}
				else {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = FLOOR;
				}

				object = (*map)[(*playerXY)[1] + 1][(*playerXY)[0]];

				(*playerXY)[1] += 1;

				(*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
			}
			break;
		case 5:	// NW
			if (!(((*map)[(*playerXY)[1] - 1][(*playerXY)[0] - 1] == TL_WALL) || ((*map)[(*playerXY)[1] - 1][(*playerXY)[0] - 1] == TB_WALL) || ((*map)[(*playerXY)[1] - 1][(*playerXY)[0] - 1] == SIDE_WALL))) {
				if (object != "") {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = object;
				}
				else {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = FLOOR;
				}

				object = (*map)[(*playerXY)[1] - 1][(*playerXY)[0] - 1];

				(*playerXY)[0] -= 1;
				(*playerXY)[1] -= 1;

				(*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
			}
			break;
		case 6:	// NE
			if (!(((*map)[(*playerXY)[1] - 1][(*playerXY)[0] + 1] == TR_WALL) || ((*map)[(*playerXY)[1] - 1][(*playerXY)[0] + 1] == TB_WALL) || ((*map)[(*playerXY)[1] - 1][(*playerXY)[0] + 1] == SIDE_WALL))) {
				if (object != "") {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = object;
				}
				else {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = FLOOR;
				}

				object = (*map)[(*playerXY)[1] - 1][(*playerXY)[0] + 1];

				(*playerXY)[0] += 1;
				(*playerXY)[1] -= 1;

				(*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
			}
			break;
		case 7:	// SW
			if (!(((*map)[(*playerXY)[1] + 1][(*playerXY)[0] - 1] == BL_WALL) || ((*map)[(*playerXY)[1] + 1][(*playerXY)[0] - 1] == TB_WALL) || ((*map)[(*playerXY)[1] + 1][(*playerXY)[0] - 1] == SIDE_WALL))) {
				if (object != "") {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = object;
				}
				else {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = FLOOR;
				}

				object = (*map)[(*playerXY)[1] + 1][(*playerXY)[0] - 1];

				(*playerXY)[0] -= 1;
				(*playerXY)[1] += 1;

				(*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
			}
			break;
		case 8:	// SE
			if (!(((*map)[(*playerXY)[1] + 1][(*playerXY)[0] + 1] == BR_WALL) || ((*map)[(*playerXY)[1] + 1][(*playerXY)[0] + 1] == TB_WALL) || ((*map)[(*playerXY)[1] + 1][(*playerXY)[0] + 1] == SIDE_WALL))) {
				if (object != "") {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = object;
				}
				else {
					(*map)[(*playerXY)[1]][(*playerXY)[0]] = FLOOR;
				}

				object = (*map)[(*playerXY)[1] + 1][(*playerXY)[0] + 1];

				(*playerXY)[0] += 1;
				(*playerXY)[1] += 1;

				(*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
			}
			break;
		default:
			cout << "How did you even get here?  Can't help you :(" << endl;
	}

	drawMap(map);
	
	keyDetector(map, playerXY, object);
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




// DEBUG
void keys() {
	int ch = 0;

	while ((ch = _getch()) != 27) {
		if (ch == 0 || ch == 224) {
			cout << _getch() << endl;
		}
		else {
			cout << ch << endl;
		}
	}
}
