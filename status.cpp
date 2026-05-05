/*
Contains functions to display the player's end enemies' status at the bottom of the screen

Functions:
displayStatus() : Display the palyer's information at the bottom of the map
enemyStatus() : Debug function to display all enemies' information below the player's
*/

#include <iostream>
#include <iomanip>
#include <string>

#include "classes.h"
#include "structs.h"

using namespace std;


void displayStatus(playerType& player) {
	string level = "Level: " + to_string(player.level) + ":" + to_string(player.xp);
	string hp = "Health: " + to_string(player.health) + "(" + to_string(player.maxHealth) + ")";
	string str = "Strength: " + to_string(player.strength);
	string gold = "Gold: " + to_string(player.gold);

	cout << "\033[22H";
	cout << left
		<< setw(19) << level
		<< setw(19) << hp
		<< setw(19) << str
		<< setw(19) << gold
		<< flush;
}

void enemyStatus(vector<Enemy*>& enemies) {
	int i = 3;

	for (auto enemy : enemies) {
		string name = enemy->getName();
		string hp = "HP: " + to_string(enemy->getHealth());
		string dmg = "DMG: " + to_string(enemy->getDamage());
		string xp = "XP: " + to_string(enemy->getXp());

		cout << "\033[2" << to_string(i) << "H";
		cout << left
			<< setw(19) << name
			<< setw(19) << xp
			<< setw(19) << hp
			<< setw(19) << dmg
			<< flush;

		i++;

		cout << "\033[2" << to_string(i) << "H"
			<< CLEAR_LINE << flush;
	}
	
}
