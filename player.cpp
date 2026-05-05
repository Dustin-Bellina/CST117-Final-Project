/*
Dustin Bellina

Contains functions that handle events directly affecting the player

Functions:
attackEnemy() : Run checks for attacking the enemy if there is one
healPlayer() : Heal the palyer a specified amount
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "defs.h"
#include "globals.h"
#include "structs.h"
#include "classes.h"

using namespace std;


void attackEnemy(string(*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType& player, vector<Enemy*>& enemies, int x, int y) {
    Enemy* enemy = nullptr;
    int vectorPos = 0;

    for (Enemy* e : enemies) {
        if ((e->getX() == x) && (e->getY() == y)) {
            enemy = e;
            break;
        }
        vectorPos++;
    }

    // Bail if there is no enemy
    if (enemy == nullptr) return;

    string enemyName = enemy->getName();

    int hitScore = enemy->getAC() - STRENGTH_MODIFIER(player.strength);
    int hitRoll = rollDie(20);

    enemy->setAggro(true);

    if (hitRoll >= hitScore) {
        damageEnemy(player, enemy);

        message(PLAYER_HIT_MESSAGES[rollDie(4) - 1] + enemyName);

        if (!enemy->isAlive()) {
            killEnemy(player, map, enemies, enemy, vectorPos);
        }
    }
    else {
        message(PLAYER_MISS_MESSAGES[rollDie(3) - 1] + enemyName);
    }

    TURN = 0;
}

void healPlayer(playerType& player, int healAmount) {
    int newHealth = player.health + healAmount;

    if (newHealth >= player.maxHealth) {
        player.health = player.maxHealth;
    }
    else {
        player.health = newHealth;
    }
}
