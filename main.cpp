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

	//#define DEBUG_MODE
	#ifdef DEBUG_MODE
		keys();
	#else
		cout << "\033[?25l";	// Hide the cursor to look more professional

		string map[MAP_HEIGHT][MAP_WIDTH];
		playerType player;

		initializePlayer(player);

		mainMenu(player);

		generateTown(&map, player);
		drawMap(&map);

		inputDetector(&map, player);
	#endif

	return 0;
}
