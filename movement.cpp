/*
Dustin Bellina

Functions:
	keyDetector(): detect when a key is pressed
	movemenrHandler(): handle movement

*/

#include <conio.h>	// Keyboard handling
#include <iostream>
#include <string>

#include "defs.h"
#include "prototypes.h"


using namespace std;



void keyDetector(string(*map)[MAP_HEIGHT][MAP_WIDTH], int (*playerXY)[2], string object) {
    int ch = 0;

    while ((ch = _getch()) != 27) {
        if (ch == 0 || ch == 224) {
            switch (_getch()) {
            case KEY_UP:    movementHandler(map, 1, playerXY, object); break;
            case KEY_LEFT:  movementHandler(map, 2, playerXY, object); break;
            case KEY_RIGHT: movementHandler(map, 3, playerXY, object); break;
            case KEY_DOWN:  movementHandler(map, 4, playerXY, object); break;
            }
        }
        else {
            switch (ch) {
            case KEY_8: movementHandler(map, 1, playerXY, object); break;
            case KEY_4: movementHandler(map, 2, playerXY, object); break;
            case KEY_6: movementHandler(map, 3, playerXY, object); break;
            case KEY_2: movementHandler(map, 4, playerXY, object); break;
            case KEY_7: movementHandler(map, 5, playerXY, object); break;
            case KEY_9: movementHandler(map, 6, playerXY, object); break;
            case KEY_1: movementHandler(map, 7, playerXY, object); break;
            case KEY_3: movementHandler(map, 8, playerXY, object); break;
            }
        }
    }
}

void movementHandler(string(*map)[MAP_HEIGHT][MAP_WIDTH], int direction, int (*playerXY)[2], string& object) {
    switch (direction) {
        case 1: // Up
            if (!((*map)[(*playerXY)[1] - 1][(*playerXY)[0]] == TB_WALL)) {
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = (object != "") ? object : FLOOR;

                object = (*map)[(*playerXY)[1] - 1][(*playerXY)[0]];
            
                (*playerXY)[1] -= 1;
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
            }
            break;
        case 2: // Left
            if (!((*map)[(*playerXY)[1]][(*playerXY)[0] - 1] == SIDE_WALL)) {
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = (object != "") ? object : FLOOR;
            
                object = (*map)[(*playerXY)[1]][(*playerXY)[0] - 1];
            
                (*playerXY)[0] -= 1;
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
            }
            break;
        case 3: // Right
            if (!((*map)[(*playerXY)[1]][(*playerXY)[0] + 1] == SIDE_WALL)) {
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = (object != "") ? object : FLOOR;
            
                object = (*map)[(*playerXY)[1]][(*playerXY)[0] + 1];
            
                (*playerXY)[0] += 1;
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
            }
            break;
        case 4: // Down
            if (!((*map)[(*playerXY)[1] + 1][(*playerXY)[0]] == TB_WALL)) {
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = (object != "") ? object : FLOOR;
            
                object = (*map)[(*playerXY)[1] + 1][(*playerXY)[0]];
            
                (*playerXY)[1] += 1;
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
            }
            break;
        case 5: // NW
            if (!(((*map)[(*playerXY)[1] - 1][(*playerXY)[0] - 1] == TL_WALL) ||
                ((*map)[(*playerXY)[1] - 1][(*playerXY)[0] - 1] == TB_WALL) ||
                ((*map)[(*playerXY)[1] - 1][(*playerXY)[0] - 1] == SIDE_WALL))) {
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = (object != "") ? object : FLOOR;
            
                object = (*map)[(*playerXY)[1] - 1][(*playerXY)[0] - 1];
            
                (*playerXY)[0] -= 1;
            
                (*playerXY)[1] -= 1;
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
            }
            break;
        case 6: // NE
            if (!(((*map)[(*playerXY)[1] - 1][(*playerXY)[0] + 1] == TR_WALL) ||
                ((*map)[(*playerXY)[1] - 1][(*playerXY)[0] + 1] == TB_WALL) ||
                ((*map)[(*playerXY)[1] - 1][(*playerXY)[0] + 1] == SIDE_WALL))) {
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = (object != "") ? object : FLOOR;
            
                object = (*map)[(*playerXY)[1] - 1][(*playerXY)[0] + 1];
            
                (*playerXY)[0] += 1;
            
                (*playerXY)[1] -= 1;
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
            }
            break;
        case 7: // SW
            if (!(((*map)[(*playerXY)[1] + 1][(*playerXY)[0] - 1] == BL_WALL) ||
                ((*map)[(*playerXY)[1] + 1][(*playerXY)[0] - 1] == TB_WALL) ||
                ((*map)[(*playerXY)[1] + 1][(*playerXY)[0] - 1] == SIDE_WALL))) {
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = (object != "") ? object : FLOOR;
            
                object = (*map)[(*playerXY)[1] + 1][(*playerXY)[0] - 1];
            
                (*playerXY)[0] -= 1;
            
                (*playerXY)[1] += 1;
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = PLAYER;
            }
            break;
        case 8: // SE
            if (!(((*map)[(*playerXY)[1] + 1][(*playerXY)[0] + 1] == BR_WALL) ||
                ((*map)[(*playerXY)[1] + 1][(*playerXY)[0] + 1] == TB_WALL) ||
                ((*map)[(*playerXY)[1] + 1][(*playerXY)[0] + 1] == SIDE_WALL))) {
            
                (*map)[(*playerXY)[1]][(*playerXY)[0]] = (object != "") ? object : FLOOR;
            
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
