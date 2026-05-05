/*
Dustin Bellina

Contains functions to handle player's inputs throughout the game

Functions:
inputDetector() : Detect when the plyer presses a button and perform the corresponding action
*/

#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "classes.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;

void inputDetector(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, vector<Enemy*>& enemies, string& object) {
    int input = _getch();
    bool redraw = false;

    te_print("");

    if (!(input == 0 || input == 224)) {
        switch (input) {
            // Movement
            case KEY_1: movementHandler(map, 7, player, object, enemies); break;
            case KEY_2: movementHandler(map, 4, player, object, enemies); break;
            case KEY_3: movementHandler(map, 8, player, object, enemies); break;
            case KEY_4: movementHandler(map, 2, player, object, enemies); break;
            case KEY_6: movementHandler(map, 3, player, object, enemies); break;
            case KEY_7: movementHandler(map, 5, player, object, enemies); break;
            case KEY_8: movementHandler(map, 1, player, object, enemies); break;
            case KEY_9: movementHandler(map, 6, player, object, enemies); break;

            // Menus
            case KEY_e: breadMenu(player); redraw = true; break;
            case KEY_i: inventoryMenu(player); redraw = true; break;
            case KEY_s: statsMenu(player); redraw = true; break;

            // Special Menus
            case KEY_ENTER:         menuHandler(map, player, enemies, object); redraw = true; break;
            case KEY_ESC:           mainMenu(player); redraw = true; break;
            case KEY_FORWARD_SLASH: helpMenu(); redraw = true; break;

            // DEBUG
            case KEY_g: if (GODMODE) menuHandler(map, player, enemies, object = ENTERANCE); redraw = true; break;
            case KEY_d: if (GODMODE) deathMenu(player); break;
            case KEY_c: if (GODMODE) winMenu(player); break;

            default:
                cout << CURSOR_HOME << CLEAR_LINE << "Illegal command: " << (char)input << flush;
        }

        if (redraw) drawMap(map, player, object);
    }
    else {
        switch (_getch()) {
            case KEY_UP:    movementHandler(map, 1, player, object, enemies); break;
            case KEY_LEFT:  movementHandler(map, 2, player, object, enemies); break;
            case KEY_RIGHT: movementHandler(map, 3, player, object, enemies); break;
            case KEY_DOWN:  movementHandler(map, 4, player, object, enemies); break;
            case KEY_HOME:  movementHandler(map, 5, player, object, enemies); break;
            case KEY_PgUp:  movementHandler(map, 6, player, object, enemies); break;
            case KEY_END:   movementHandler(map, 7, player, object, enemies); break;
            case KEY_PgDn:  movementHandler(map, 8, player, object, enemies); break;
        }
    }
}
