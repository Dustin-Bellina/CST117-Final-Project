#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include "defs.h"
#include "globals.h"
#include "classes.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;

int main() {
	// Ensure Windows displays the characters properly
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    // Hide the cursor so it's not an eyesore
    hideCursor();

    string map[2][MAP_HEIGHT][MAP_WIDTH];   // Map is broken into 2 layers: The actual map, and what is revealed in the map
    playerType player;

    vector<Enemy*> enemies;
    enemies.reserve(MAX_ENEMIES);

    initializePlayer(player);

    mainMenu(player);

    loadLevel(&map, player, enemies);
    drawMap(&map, player);

    displayStatus(player);

    string object = "";

    // Game Loop
    while (true) {
        // Let the player take their turn
        inputDetector(&map, player, enemies, object);

        // Let every enemy take their turn if they are aggro'd
        for (Enemy* e : enemies) {
            if (e->getAggro()) {
                enemyTurn(&map, player, e);
            }
        }

        // Print all messages
        flushMessages();

        // Heal the player every 10 non-combatant turns
        if (TURN == 10) {
            healPlayer(player, rollDie(4));
            TURN = 0;
        }

        // Display the player's status
        displayStatus(player);

        if (DEBUG_ENEMIES) enemyStatus(enemies);
    }

    return 0;
}
