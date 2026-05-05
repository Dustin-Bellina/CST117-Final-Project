/*
Dustin Bellina

Contains functions that directly affect the enemy

Functions:
isEnemy() : Return true if the specified object is an enemy
damageEnemy() : Remove a specified amount of HP from the specified enemy
killEnemy() : Send a kill message and remove the specified enemy from the vector
clearEnemies() : Clear the enemy vector
*/

#include <iostream>
#include <string>
#include <cmath>

#include "defs.h"
#include "globals.h"
#include "classes.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;


bool isEnemy(string object) {
    for (auto ch : ENEMY_LIST) {
        if (object == ch) return true;
    }

    for (auto ch : BOSS_LIST) {
        if (object == ch) return true;
    }

    return false;
}

void damageEnemy(playerType& player, Enemy* enemy) {
    enemy->takeDamage(PLAYER_DAMAGE);
}

void killEnemy(playerType& player, string(*map)[2][MAP_HEIGHT][MAP_WIDTH], vector<Enemy*>& enemies, Enemy* enemy, int vectorPos) {
    (*map)[0][enemy->getY()][enemy->getX()] = FLOOR;
    
    killMessage(enemy->getName());
    awardXP(player, enemy->getXp());

    delete enemies[vectorPos];
    enemies.erase(enemies.begin() + vectorPos);
}

void clearEnemies(vector<Enemy*>& enemies) {
    for (Enemy* e : enemies) delete e;
    enemies.clear();
}

void killMessage(string enemyName) {
    message(KILL_MESSAGES[rollDie(4) - 1] + enemyName);
}

void enemyTurn(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, Enemy* enemy) {
    // See if the player is within attack range (1 block in every direction)
    bool found = false;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int x = enemy->getX() + i;
            int y = enemy->getY() + j;
            if ((x >= 0 && x < MAP_WIDTH) && (y >= 0 && y < MAP_HEIGHT)) {
                if ((*map)[0][y][x] == PLAYER) {
                    found = true;
                    break;
                }
            }
        }
        if (found) break;
    }

    if (found) {
        int hitRoll = rollDie(20);
        int hitScore = player.armorClass;
        if (hitRoll >= hitScore) {
            attackPlayer(player, enemy->getDamage());
            message("The " + enemy->getName() + ENEMY_HIT_MESSAGES[rollDie(4) - 1]);
        }
        else {
            message("The " + enemy->getName() + ENEMY_MISS_MESSAGES[rollDie(3) - 1]);
        }
    }
    elif(enemy->getAggro()) {
        moveEnemy(map, player, enemy);
    }
}

void attackPlayer(playerType& player, int damage) {
    player.health -= damage;

    if (player.health <= 0 && !GODMODE) {
        deathMenu(player);
    }
}

// Bresenham's line algorithm derived from generateHall()@map_generation.cpp
void moveEnemy(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, Enemy* enemy) {
    int x1 = enemy->getX(), y1 = enemy->getY();
    int x2 = player.x, y2 = player.y;

    int dx = abs(x2 - x1), sx = (x1 < x2) ? 1 : -1;
    int dy = -abs(y2 - y1), sy = (y1 < y2) ? 1 : -1;
    int err = dx + dy;
    int e2 = 2 * err;

    int newX = x1, newY = y1;
    if (e2 >= dy) newX += sx;
    if (e2 <= dx) newY += sy;

    string& target = (*map)[0][newY][newX];
    if ((target != DOOR) &&
        (target != TB_WALL) &&
        (target != SIDE_WALL) &&
        (target != TL_WALL) &&
        (target != TR_WALL) &&
        (target != BL_WALL) &&
        (target != BR_WALL) &&
        (target != PLAYER)) {

        if (isEnemy(target)) return;

        (*map)[0][y1][x1] = FLOOR;
        enemy->setXY(newX, newY);
        (*map)[0][newY][newX] = enemy->getSymbol();

        if ((*map)[1][y1][x1] == "1")       drawCell(map, x1, y1);
        if ((*map)[1][newY][newX] == "1")   drawCell(map, newX, newY);
    }
}

void generateEnemies(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], vector<Enemy*>& enemies, string stage, int rW, int rH, int rX, int rY) {
    int enemyCount = 0;

    for (int i = 0; i < MAX_ENEMIES + 2 && enemyCount < MAX_ENEMIES; i++) {
        if (rollDie(2) == 1) {
            int ex, ey;
            int attempts = 0;
            do {
                ex = rX + 1 + rand() % ((rX + rW - 1) - rX - 1);
                ey = rY + 1 + rand() % ((rY + rH - 1) - rY - 1);
                attempts++;
            } while ((*map)[0][ey][ex] != FLOOR && attempts < 10);

            if ((*map)[0][ey][ex] != FLOOR) continue;

            Enemy* e = nullptr;

            if      (stage == "SEWER")  e = spawnSewerEnemy();
            elif    (stage == "CAVE")   e = spawnCaveEnemy();
            elif    (stage == "FOREST") e = spawnForestEnemy();
            elif    (stage == "CASTLE") e = spawnCastleEnemy();

            if (e != nullptr) {
                e->setXY(ex, ey);
                (*map)[0][ey][ex] = e->getSymbol();
                enemies.push_back(e);
                enemyCount++;
            }
        }
    }
}

void generateBoss(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], vector<Enemy*>& enemies, string stage, int rW, int rH, int rX, int rY) {
    int ex, ey;
    do {
        ex = rX + 1 + rand() % ((rX + rW - 1) - rX - 1);
        ey = rY + 1 + rand() % ((rY + rH - 1) - rY - 1);
    } while ((*map)[0][ey][ex] != FLOOR && !isEnemy((*map)[0][ey][ex]));

    Enemy* e = nullptr;

    if (stage == "SEWER")  e = new Orog();
    elif(stage == "CAVE")   e = new Dragon();
    elif(stage == "FOREST") e = new Treant();
    elif(stage == "CASTLE") e = new VampireKing();

    if (e != nullptr) {
        e->setXY(ex, ey);
        (*map)[0][ey][ex] = e->getSymbol();
        enemies.push_back(e);
    }
}

Enemy* spawnSewerEnemy() {
    switch (rollDie(3)) {
        case 1: return new Rat();
        case 2: return new SewerGoblin();
        case 3: return new Slime();
        default: return nullptr;
    }
}

Enemy* spawnCaveEnemy() {
    switch (rollDie(3)) {
        case 1: return new Bat();
        case 2: return new CaveGoblin();
        case 3: return new CaveOrc();
        default: return nullptr;
    }
}

Enemy* spawnForestEnemy() {
    switch (rollDie(3)) {
        case 1: return new Werewolf();
        case 2: return new Elf();
        case 3: return new Monkey();
        default: return nullptr;
    }
}

Enemy* spawnCastleEnemy() {
    switch (rollDie(3)) {
        case 1: return new Vampire();
        case 2: return new Hobgoblin();
        case 3: return new CastleOrc();
        default: return nullptr;
    }
}
