/*
Dustin Bellina

Functions:
    inputDetector(): detect when a key is pressed

    keys(): NEED TO REMOVE debug function to see what code a key sends
*/

#include <conio.h>	// Keyboard handling
#include <iostream>
#include <string>

#include "defs.h"
#include "prototypes.h"


using namespace std;


void inputDetector(string (*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player) {
    string object = "";

    int input = 0;

    while (true) {
        input = _getch();

        if (input == 0 || input == 224) { // Separate some special keys.  These keys send two ch codes, so _getch() must be run twice to get the actual input
            switch (_getch()) {
                case KEY_UP:    movementHandler(map, 1, player, object); break;
                case KEY_LEFT:  movementHandler(map, 2, player, object); break;
                case KEY_RIGHT: movementHandler(map, 3, player, object); break;
                case KEY_DOWN:  movementHandler(map, 4, player, object); break;
            }
        }
        else {
            switch (input) {
                // Movement
                case KEY_8: movementHandler(map, 1, player, object); break;
                case KEY_4: movementHandler(map, 2, player, object); break;
                case KEY_6: movementHandler(map, 3, player, object); break;
                case KEY_2: movementHandler(map, 4, player, object); break;
                case KEY_7: movementHandler(map, 5, player, object); break;
                case KEY_9: movementHandler(map, 6, player, object); break;
                case KEY_1: movementHandler(map, 7, player, object); break;
                case KEY_3: movementHandler(map, 8, player, object); break;

                case KEY_e: breadMenu(player); break;
                case KEY_i: inventoryMenu(player); break;
                case KEY_s: statsMenu(player); break;

                case KEY_ENTER: menuHandler(map, player, object); break;
                case KEY_ESC: mainMenu(player);  break;
                case KEY_FORWARD_SLASH: helpMenu(); break;

                // DEBUG - REMOVE
                case KEY_g: menuHandler(map, player, object = SEWER_ENTERANCE); break;

                default: cout << CURSOR_HOME << CLEAR_LINE << "Illegal command: " << (char)input << flush; continue;
            }
        }

        drawMap(map, object);
    }
}




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
