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


void movementHandler(string(*map)[MAP_HEIGHT][MAP_WIDTH], int direction, playerType &player, string &object) {
    string dirObj;  // Object in direction of travel

    switch (direction) {
        case 1: // Up
            dirObj = (*map)[player.y - 1][player.x];

            if (!((dirObj == TB_WALL) ||
                (dirObj == SIDE_WALL) ||
                (dirObj == TL_WALL) ||
                (dirObj == TR_WALL) ||
                (dirObj == BL_WALL) ||
                (dirObj == BR_WALL) ||
                (dirObj == " "))) {

                (*map)[player.y][player.x] = (object != "") ? object : FLOOR;

                object = dirObj;

                player.y -= 1;

                (*map)[player.y][player.x] = PLAYER;
            }
            break;
        case 2: // Left
            dirObj = (*map)[player.y][player.x - 1];

            if (!((dirObj == TB_WALL) ||
                (dirObj == SIDE_WALL) ||
                (dirObj == TL_WALL) ||
                (dirObj == TR_WALL) ||
                (dirObj == BL_WALL) ||
                (dirObj == BR_WALL) ||
                (dirObj == " "))) {

                (*map)[player.y][player.x] = (object != "") ? object : FLOOR;

                object = (*map)[player.y][player.x - 1];

                player.x -= 1;

                (*map)[player.y][player.x] = PLAYER;
            }
            break;
        case 3: // Right
            dirObj = (*map)[player.y][player.x + 1];

            if (!((dirObj == TB_WALL) ||
                (dirObj == SIDE_WALL) ||
                (dirObj == TL_WALL) ||
                (dirObj == TR_WALL) ||
                (dirObj == BL_WALL) ||
                (dirObj == BR_WALL) ||
                (dirObj == " "))) {

                (*map)[player.y][player.x] = (object != "") ? object : FLOOR;

                object = dirObj;

                player.x += 1;

                (*map)[player.y][player.x] = PLAYER;
            }
            break;
        case 4: // Down
            dirObj = (*map)[player.y + 1][player.x];

            if (!((dirObj == TB_WALL) ||
                (dirObj == SIDE_WALL) ||
                (dirObj == TL_WALL) ||
                (dirObj == TR_WALL) ||
                (dirObj == BL_WALL) ||
                (dirObj == BR_WALL) ||
                (dirObj == " "))) {

                (*map)[player.y][player.x] = (object != "") ? object : FLOOR;

                object = dirObj;

                player.y += 1;

                (*map)[player.y][player.x] = PLAYER;
            }
            break;
        case 5: // NW
            dirObj = (*map)[player.y - 1][player.x - 1];

            if (!((dirObj == TB_WALL) ||
                (dirObj == SIDE_WALL) ||
                (dirObj == TL_WALL) ||
                (dirObj == TR_WALL) ||
                (dirObj == BL_WALL) ||
                (dirObj == BR_WALL) ||
                (dirObj == " "))) {

                (*map)[player.y][player.x] = (object != "") ? object : FLOOR;

                object = dirObj;

                player.x -= 1;
                player.y -= 1;

                (*map)[player.y][player.x] = PLAYER;
            }
            break;
        case 6: // NE
            dirObj = (*map)[player.y - 1][player.x + 1];

            if (!((dirObj == TB_WALL) ||
                (dirObj == SIDE_WALL) ||
                (dirObj == TL_WALL) ||
                (dirObj == TR_WALL) ||
                (dirObj == BL_WALL) ||
                (dirObj == BR_WALL) ||
                (dirObj == " "))) {

                (*map)[player.y][player.x] = (object != "") ? object : FLOOR;

                object = dirObj;

                player.x += 1;
                player.y -= 1;

                (*map)[player.y][player.x] = PLAYER;
            }
            break;
        case 7: // SW
            dirObj = (*map)[player.y + 1][player.x - 1];

            if (!((dirObj == TB_WALL) ||
                (dirObj == SIDE_WALL) ||
                (dirObj == TL_WALL) ||
                (dirObj == TR_WALL) ||
                (dirObj == BL_WALL) ||
                (dirObj == BR_WALL) ||
                (dirObj == " "))) {

                (*map)[player.y][player.x] = (object != "") ? object : FLOOR;

                object = dirObj;

                player.x -= 1;
                player.y += 1;

                (*map)[player.y][player.x] = PLAYER;
            }
            break;
        case 8: // SE
            dirObj = (*map)[player.y + 1][player.x + 1];

            if (!((dirObj == TB_WALL) ||
                (dirObj == SIDE_WALL) ||
                (dirObj == TL_WALL) ||
                (dirObj == TR_WALL) ||
                (dirObj == BL_WALL) ||
                (dirObj == BR_WALL) ||
                (dirObj == " "))) {

                (*map)[player.y][player.x] = (object != "") ? object : FLOOR;

                object = dirObj;

                player.x += 1;
                player.y += 1;

                (*map)[player.y][player.x] = PLAYER;
            }
            break;
        default:
            cout << "An unexpected error has occurred in movementHandler()" << endl; exit;
    }
}
