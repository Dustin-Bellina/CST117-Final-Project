/*
Dustin Bellina
*/

#include <iostream>
#include <string>

#ifdef _WIN32
	#include <windows.h>	// Windows API
#endif

#include "defs.h"
#include "prototypes.h"

using namespace std;


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
