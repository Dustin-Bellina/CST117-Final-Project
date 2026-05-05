/*
Contains functions relating to the level and experience system in the game

Functions:
awardXP() : Add to the player's XP total
levelHandler() : Level up and increase the player's max HP if they exceed a certain threshold
*/

#include <iostream>

#include "defs.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;

void awardXP(playerType &player, int xp) {
	player.xp += xp;

	levelHandler(player);
}

void levelHandler(playerType& player) {
	int xp = player.xp;
	int level = player.level;

	if		(xp >= 262144)	player.level = 8;	// Good luck
	elif	(xp >= 65536)	player.level = 7;
	elif	(xp >= 16384)	player.level = 6;
	elif	(xp >= 4096)	player.level = 5;
	elif	(xp >= 1024)	player.level = 4;
	elif	(xp >= 256)		player.level = 3;
	elif	(xp >= 64)		player.level = 2;
	elif	(xp >= 16)		player.level = 1;

	// Send a message and ncrease player's max health if they increase in level
	if (player.level != level) {
		message("You are now level " + to_string(player.level));
		player.maxHealth += rollDie(8);
	}
}
