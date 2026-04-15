#include <iostream>
#include <string>

#ifdef _WIN32
	#include <windows.h>	// Windows API
#endif

#include "defs.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;


void keys();


int main() {
	// Ensure Windows outputs the wall characters properly
	#ifdef _WIN32
		SetConsoleOutputCP(65001);
	#endif

	cout << "\033[?25l";	// Hide the cursor

	string map[MAP_HEIGHT][MAP_WIDTH];
	playerType player;
	int playerXY[2];

	initializePlayer(player);

	mainMenu(player);

	generateTown(&map, &playerXY);

	inputDetector(&map, player, &playerXY, "");

	return 0;
}
