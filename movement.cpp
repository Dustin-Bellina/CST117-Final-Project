/*
Dustin Bellina

Contains functions to handle player movement

Functions:
movementHandler() : When the player tries to move in a direction, run checks and handle accordingly
*/

#include <iostream>
#include <string>

#include "defs.h"
#include "globals.h"
#include "classes.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;

void movementHandler(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], int direction, playerType& player, string& object, vector<Enemy*>& enemies) {
    string dirObj;
    int x = player.x;
    int y = player.y;

    // Load the object in the direction the player is moving into dirObj (directionObject)
    if      (direction == 1 && player.y - 1 >= 0)                                       { x = player.x;     y = player.y - 1; dirObj = (*map)[0][y][x]; }
    elif    (direction == 2 && player.x - 1 >= 0)                                       { x = player.x - 1; y = player.y;     dirObj = (*map)[0][y][x]; }
    elif    (direction == 3 && player.x + 1 < MAP_WIDTH)                                { x = player.x + 1; y = player.y;     dirObj = (*map)[0][y][x]; }
    elif    (direction == 4 && player.y + 1 < MAP_HEIGHT)                               { x = player.x;     y = player.y + 1; dirObj = (*map)[0][y][x]; }
    elif    (direction == 5 && player.x - 1 >= 0 && player.y - 1 >= 0)                  { x = player.x - 1; y = player.y - 1; dirObj = (*map)[0][y][x]; }
    elif    (direction == 6 && player.x + 1 < MAP_WIDTH && player.y - 1 >= 0)           { x = player.x + 1; y = player.y - 1; dirObj = (*map)[0][y][x]; }
    elif    (direction == 7 && player.x - 1 >= 0 && player.y + 1 < MAP_HEIGHT)          { x = player.x - 1; y = player.y + 1; dirObj = (*map)[0][y][x]; }
    elif    (direction == 8 && player.x + 1 < MAP_WIDTH && player.y + 1 < MAP_HEIGHT)   { x = player.x + 1; y = player.y + 1; dirObj = (*map)[0][y][x]; }

    // Check if the player is running into an enemy and attack if so
    if (isEnemy(dirObj)) {
        attackEnemy(map, player, enemies, x, y);
        drawCell(map, x, y);
        return;
    }

    // Handle movement
    if (dirObj != "" &&
        !((dirObj == TB_WALL) ||
            (dirObj == SIDE_WALL) ||
            (dirObj == TL_WALL) ||
            (dirObj == TR_WALL) ||
            (dirObj == BL_WALL) ||
            (dirObj == BR_WALL) ||
            (dirObj == " "))) {

        switch (direction) {
            /*
            * General Logic Flow:
            * 1. If the object the player is currently stnding on is not FLOOR, set the cell to that object.  Otherwise, set it to FLOOR again
            * 2. Change the player's xy
            * 3. Set the map cell in the direction the player is going to the player
            */
        case 1: // UP
            if (player.y - 1 >= 0) {
                (*map)[0][player.y][player.x] = (object != "") ? object : FLOOR;
                player.y -= 1;
                (*map)[0][player.y][player.x] = PLAYER;
            }
            break;
        case 2: // LEFT
            if (player.x - 1 >= 0) {
                (*map)[0][player.y][player.x] = (object != "") ? object : FLOOR;
                player.x -= 1;
                (*map)[0][player.y][player.x] = PLAYER;
            }
            break;
        case 3: // RIGHT
            if (player.x + 1 < MAP_WIDTH) {
                (*map)[0][player.y][player.x] = (object != "") ? object : FLOOR;
                player.x += 1;
                (*map)[0][player.y][player.x] = PLAYER;
            }
            break;
        case 4: // DOWN
            if (player.y + 1 < MAP_HEIGHT) {
                (*map)[0][player.y][player.x] = (object != "") ? object : FLOOR;
                player.y += 1;
                (*map)[0][player.y][player.x] = PLAYER;
            }
            break;
        case 5: // NW
            if (player.x - 1 >= 0 && player.y - 1 >= 0) {
                (*map)[0][player.y][player.x] = (object != "") ? object : FLOOR;
                player.x -= 1;
                player.y -= 1;
                (*map)[0][player.y][player.x] = PLAYER;
            }
            break;
        case 6: // NE
            if (player.x + 1 < MAP_WIDTH && player.y - 1 >= 0) {
                (*map)[0][player.y][player.x] = (object != "") ? object : FLOOR;
                player.x += 1;
                player.y -= 1;
                (*map)[0][player.y][player.x] = PLAYER;
            }
            break;
        case 7: // SW
            if (player.x - 1 >= 0 && player.y + 1 < MAP_HEIGHT) {
                (*map)[0][player.y][player.x] = (object != "") ? object : FLOOR;
                player.x -= 1;
                player.y += 1;
                (*map)[0][player.y][player.x] = PLAYER;
            }
            break;
        case 8: // SE
            if (player.x + 1 < MAP_WIDTH && player.y + 1 < MAP_HEIGHT) {
                (*map)[0][player.y][player.x] = (object != "") ? object : FLOOR;
                player.x += 1;
                player.y += 1;
                (*map)[0][player.y][player.x] = PLAYER;
            }
            break;
        default:
            te_error("Illegal movement direction: " + to_string(direction));
            showCursor();
            exit(1);
        }

        // Set the new object variable to the object the player is currently standing on
        object = dirObj;
    }

    // Update the 9 cells around and including the player
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int cx = player.x + i;
            int cy = player.y + j;
            if ((cx >= 0 && cx < MAP_WIDTH) && (cy >= 0 && cy < MAP_HEIGHT)) {
                drawCell(map, cx, cy, object);
            }
        }
    }
    drawCell(map, player.x, player.y, object);

    // If the player enters a room, reveal the whole room
    if (dirObj == DOOR) {
        roomType room = drawRoom(map, player.x, player.y);
        if (room.x1 != -1) {
            for (int i = room.y1; i <= room.y2; i++) {
                for (int j = room.x1; j <= room.x2; j++) {
                    drawCell(map, j, i, object);
                }
            }
        }
    }

    // If the object the player is standing on is an item, pick it up
    if (isItem(object)) pickupItem(map, player, object);

    TURN++;
}
