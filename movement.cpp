/*
Dustin Bellina

Functions:
	movemenrHandler(): handle movement
*/

#include <iostream>
#include <string>

#include "defs.h"
#include "prototypes.h"


using namespace std;


void movementHandler(string(*map)[MAP_HEIGHT][MAP_WIDTH], int direction, int (*playerXY)[2], string &object) {
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
