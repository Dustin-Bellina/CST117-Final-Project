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


void inputDetector(string (*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player, int (*playerXY)[2], string object) {
    int ch = 0;

    while (true) {
        ch = _getch();

        if (ch == 0 || ch == 224) { // Separate the special keys.  Since they send two ch codes, _getch() must be run twice to get the actual input
                switch (_getch()) {
                case KEY_UP:    movementHandler(map, 1, playerXY, object); break;
                case KEY_LEFT:  movementHandler(map, 2, playerXY, object); break;
                case KEY_RIGHT: movementHandler(map, 3, playerXY, object); break;
                case KEY_DOWN:  movementHandler(map, 4, playerXY, object); break;
            }
        }
        else {
            switch (ch) {
                // Movement
                case KEY_8: movementHandler(map, 1, playerXY, object); break;
                case KEY_4: movementHandler(map, 2, playerXY, object); break;
                case KEY_6: movementHandler(map, 3, playerXY, object); break;
                case KEY_2: movementHandler(map, 4, playerXY, object); break;
                case KEY_7: movementHandler(map, 5, playerXY, object); break;
                case KEY_9: movementHandler(map, 6, playerXY, object); break;
                case KEY_1: movementHandler(map, 7, playerXY, object); break;
                case KEY_3: movementHandler(map, 8, playerXY, object); break;

                case KEY_i: inventoryMenu(player); drawMap(map); break;

                case KEY_ENTER: menuHandler(player, object); break;

                case KEY_FORWARD_SLASH: helpMenu(); break;

                case KEY_ESC: break;

                default: cout << "\033[HUnknown command: " << (char)ch << endl; continue;   // TODO: What is clearing the screen?
            }
        }

        drawMap(map);
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