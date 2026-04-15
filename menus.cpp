/*
4/14/2026 Changelog:
: Converted player data into a struct
    + Added initializePlater() to initialize the struct
    : Edited all datapoints to reflect the change to struct
+ Added and included structs.h for the structs
+ Added includes for the defs and prototypes
: Made the couts a little more readable
: Added arguments to most functions for the integration
: Modified choice selection code to match the rest
*/

/*
Alir Louis

Functions:
*/

#include <iostream>
#include <conio.h>	// Keyboard handling
#include <string>
#include <fstream>

#include "defs.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;

int breadHealing = 5;

// If any default player data needs to be changed, it should be done in initializePlayer(). 
// If a new stat needs to be added, add it in playerType in structs.h and initialize it in initializePlayer()

// again these can be changed here and it will change everywhere in the code...i think, these are just testing numbers for the shop, they can be changed to whatever you want
int shopHealthPotionPrice = 10;
int shopStrengthPotionPrice = 15;
int shopBreadPrice = 5;
int shopHealthPotionsStock = 5;
int shopStrengthPotionsStock = 3;
int shopBreadStock = 10;

//im pretty new to this, my fault if it aint too advanced or clean
//im learning as i go, but this is just the basic structure of the game, we can add more features and functionality later on, 
// lemme know if this is too much or there's a better way to do this.

void menuHandler(playerType &player, string &object) {
    if      (object == SHOP)            { shopMenu(player); }
    elif    (object == SEWER_ENTERANCE) {}
}

void mainMenu(playerType &player) {
    int choice = 0;

    while (choice != '5') {
        clearScreen();

        cout << "\n==== TEXT ROGUELIKE ====" << "\n"
            << "1. Start Game" << "\n"
            << "2. Load Game" << "\n"
            << "3. Save Game" << "\n"
            << "4. Help" << "\n"
            << "5. Exit" << endl;

        choice = _getch();

        if (choice == '1') {
            break;
        }
        else if (choice == '2') {
            loadGame(player);
        }
        else if (choice == '3') {
            saveGame(player);
        }
        else if (choice == '4') {
            helpMenu();
        }
        else if (choice == '5') {
            saveGame(player);
            cout << "Run saved, Exiting the world..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}

void initializePlayer(playerType& player) {
    player.health = 100;
    player.strength = 10;
    player.armor = 25;
    player.healthPotions = 10;
    player.strengthPotions = 5;
    player.swordDamage = 10;
    player.bread = 5;
    player.gold = 100;
}

// of course the help menu. i placed some placeholder text in there for now, but we can change it to whatever we want, 
// this is just to give the player some information about the game and how to play it,
void helpMenu() {
    clearScreen();

    int choice = 0;

    while (choice != -1) {
        cout << "\n==== HELP ====" << "\n"
            << "This is a text-based roguelike game. Survive and save the town!" << "\n"
            << "\n==== CONTROLS ====" << "\n"
            << "Arrow Keys: Move your character" << "\n"
            << "7: Move North West" << "\n"
            << "9: Move North East" << "\n"
            << "1: Move South West" << "\n"
            << "3: Move South East" << "\n"
            << "i: Open inventory" << "\n"
            << "/: Open help menu" << "\n"
            << "\n==== MENUS ====" << "\n"
            << "In the town menu, you can go to the sewer, visit the shop, check your inventory, or view your stats." << "\n"
            << "In the inventory menu, you can manage your potions, sword, bread, and armor." << "\n"
            << "In the stats menu, you can view your current health, strength, armor, and how many potions you have." << "\n"
            << "In the shop menu, you can buy health potions, strength potions, and bread." << "\n"
            << "In the potion menu, you can drink your health and strength potions to increase your stats." << "\n"
            << "In the sword menu, you can equip, upgrade, or drop your sword." << "\n"
            << "In the armor menu, you can equip, upgrade, or drop your armor." << "\n"
            << "\n==== SAVE / LOAD ====" << "\n"
            << "You can save your game from the main menu and load it later to continue your adventure." << "\n"
            << "Good luck, and have fun playing!" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_ESC) {
            cout << "Returning to main menu..." << endl;
            choice = -1;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}

// this is the main menu for the town, you can go to the sewer, visit the shop, check your inventory, or view your stats
void townMenu(playerType& player) {
    clearScreen();

    char choice = ' ';

    while (choice != '5') {
        cout << "\n==== TOWN MENU ====" << "\n"
            << "1. Go to Sewer" << "\n"
            << "2. Visit Shop" << "\n"
            << "3. Check Inventory" << "\n"
            << "4. View Stats" << "\n"
            << "5. Return to Main Menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == '1') {
            sewerMenu(player);
        }
        else if (choice == '2') {
            shopMenu(player);
        }
        else if (choice == '3') {
            inventoryMenu(player);
        }
        else if (choice == '4') {
            statsMenu(player);
        }
        else if (choice == '5') {
            cout << "Returning to main menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
// this is the inventory menu, you can manage your potions, sword, bread, and armor here, you can also view how many of each item you have
void inventoryMenu(playerType& player) {
    clearScreen();

    int choice = 0;

    while (choice != -1) {
        cout << "\n==== INVENTORY ====" << "\n"
            << "a. Potions (" << player.healthPotions + player.strengthPotions << " total)" << "\n"
            << "b. Sword" << "\n"
            << "c. Bread (" << player.bread << " left)" << "\n"
            << "d. Armor" << "\n"
            << "ESC. Back" << endl;

        choice = _getch();

        if (choice == 'a') {
            potionMenu(player);
        }
        else if (choice == 'b') {
            swordMenu(player);
        }
        else if (choice == 'c') {
            breadMenu(player);
        }
        else if (choice == 'd') {
            armorMenu(player);
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to town..." << endl;
            choice = -1;
        }
        else {
            cout << "Invalid choice." << endl;
        }

        clearScreen();
    }
}
// this is the stats menu, you can view your current health, strength, armor, and how many potions you have, as well as your sword damage and how much gold you have!.
void statsMenu(playerType& player) {
    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n==== STATS ====" << "\n"
            << "Health: " << player.health << "\n"
            << "Strength: " << player.strength << "\n"
            << "Armor: " << player.armor << "\n"
            << "Health Potions: " << player.healthPotions << "\n"
            << "Strength Potions: " << player.strengthPotions << "\n"
            << "Sword Damage: " << player.swordDamage << "\n"
            << "Bread: " << player.bread << "\n"
            << "Gold: " << player.gold << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_ESC) {
            cout << "Returning to town menu..." << endl;
        }
        else {
            clearScreen();
            cout << "Invalid choice." << endl;
        }

    }
}
// this is the shop menu, you can buy health potions, strength potions, and bread here, the prices and stock are displayed, if you don't have enough gold or if the item is out of stock it will let you know!.
void shopMenu(playerType& player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\nWelcome to the shop!" << "\n\n"
            << "a. Buy Health Potion (" << shopHealthPotionPrice << " gold) " << shopHealthPotionsStock << " left" << "\n"
            << "b. Buy Strength Potion (" << shopStrengthPotionPrice << " gold) " << shopStrengthPotionsStock << " left" << "\n"
            << "c. Buy Bread (" << shopBreadPrice << " gold) " << shopBreadStock << " left" << "\n"
            << "\nYour gold: " << player.gold << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();
        clearScreen();

        if (choice == KEY_a) {
            if (shopHealthPotionsStock > 0) {
                if (player.gold >= shopHealthPotionPrice) {
                    cout << "You purchased a Health Potion." << endl;
                    player.healthPotions += 1;
                    shopHealthPotionsStock -= 1;
                    player.gold -= shopHealthPotionPrice;
                }
                else {
                    cout << "You don't have enough gold to buy a Health Potion!" << endl;
                }
            }
            else {
                cout << "No Health Potions left. We are out of stock, sorry!" << endl;
            }
        }
        else if (choice == KEY_b) {
            if (shopStrengthPotionsStock > 0) {
                if (player.gold >= shopStrengthPotionPrice) {
                    cout << "You purchased a Strength Potion." << endl;
                    player.strengthPotions += 1;
                    shopStrengthPotionsStock -= 1;
                    player.gold -= shopStrengthPotionPrice;
                }
                else {
                    cout << "You don't have enough gold to buy a Strength Potion!" << endl;
                }
            }
            else {
                cout << "No Strength Potions left. We are out of stock, sorry!" << endl;
            }
        }
        else if (choice == KEY_c) {
            if (shopBreadStock > 0) {
                if (player.gold >= shopBreadPrice) {
                    cout << "You purchased some Bread." << endl;
                    player.bread += 1;
                    shopBreadStock = shopBreadStock - 1;
                    player.gold -= shopBreadPrice;
                }
                else {
                    cout << "You don't have enough gold to buy Bread!" << endl;
                }
            }
            else {
                cout << "No Bread left. We are out of stock, sorry! " << endl;
            }
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to town menu..." << endl;
        }
        else {
            clearScreen();
            cout << "Invalid choice." << endl;
        }
    }
}

// this is the sewer menu, you can enter the sewer to explore and find new items and enemies, 
// you can also search the area to find hidden items or read the warning sign to get some information about the dangers that lurk in the sewer.
void sewerMenu(playerType& player) {
    char choice = ' ';

    while (choice != 'x') {
        cout << "\n==== SEWER MENU ====" << "\n"
            << "a. Enter Sewer" << "\n"
            << "b. Search Area" << "\n"
            << "c. Read Warning Sign" << "\n"
            << "x. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 'a') {
            cout << "You enter the sewer, the domain of filth. It is dark, damp, and full of danger lurking below." << endl;
        }
        else if (choice == 'b') {
            cout << "You search the area but do not find anything yet." << endl;
        }
        else if (choice == 'c') {
            cout << "The sign reads: Beware of rats, slime, and other dangers below." << endl;
        }
        else if (choice == 'x') {
            cout << "Returning to town menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
// this is the potion menu, same as the other menus, you can manage your potions here etc etc. . .
void potionMenu(playerType& player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n==== POTION MENU ====" << "\n"
            << "a. Health Potion (" << player.healthPotions << " left)" << "\n"
            << "b. Strength Potion (" << player.strengthPotions << " left)" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();
        clearScreen();

        if (choice == KEY_a) {
            if (player.healthPotions > 0) {
                player.health += 10;
                player.healthPotions -= 1;
                cout << "You drank a Health Potion. Health is now " << player.health << ".";

                if (player.healthPotions == 0) {
                    cout << " You no longer have any Health Potions left!";
                }

                cout << endl;
            }
            else {
                clearScreen();
                cout << "You have no Health Potions left!" << endl;
            }
        }
        else if (choice == KEY_b) {
            if (player.strengthPotions > 0) {
                player.strength += 5;
                player.strengthPotions -= 1;
                cout << "You drank a Strength Potion. Strength is now " << player.strength << ".";

                if (player.strengthPotions == 0) {
                    cout << " You no longer have any Strength Potions left!";
                }

                cout << endl;
            }
            else {
                clearScreen();
                cout << "You have no Strength Potions left!" << endl;
            }
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            clearScreen();
            cout << "Invalid choice." << endl;
        }
    }
}

void breadMenu(playerType& player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n==== BREAD MENU ====" << "\n"
            << "a. Eat Bread" << "\n"
            << "b. Drop Bread" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();
        clearScreen();

        if (choice == KEY_a) {
            if (player.bread > 0) {
                player.health += breadHealing;
                player.bread -= 1;

                clearScreen();
                cout << "You ate the bread. Health is now " << player.health << ".";

                if (player.bread == 0) {
                    cout << " You no longer have any bread left!";
                }

                cout << endl;
            }
            else {
                clearScreen();
                cout << "You have no bread left!" << endl;
            }
        }
        else if (choice == KEY_b) {
            if (player.bread > 0) {
                player.bread -= 1;

                clearScreen();
                cout << "You dropped the bread!" << endl;

                if (player.bread == 0) {
                    cout << "You no longer have any bread left!" << endl;
                }
            }
            else {
                clearScreen();
                cout << "You have no bread left!" << endl;
            }
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            clearScreen();
            cout << "Invalid choice." << endl;
        }
    }
}

// this is the sword menu, you can manage your sword here, you can equip it to increase your strength, upgrade it to increase your sword damage, or drop it if you want to get rid of it.
// if you drop it you will have to find another one in the sewer or buy one from the shop!
void swordMenu(playerType& player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n==== SWORD MENU ====" << "\n"
            << "a. Equip Sword" << "\n"
            << "b. Upgrade Sword" << "\n"
            << "d. Drop Sword" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_a) {
            clearScreen();
            cout << "You equipped the sword!" << endl;
        }
        else if (choice == KEY_b) {
            clearScreen();
            cout << "You upgraded your sword!" << endl;
        }
        else if (choice == KEY_d) {
            clearScreen();
            cout << "You dropped your sword!" << endl;
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            clearScreen();
            cout << "Invalid choice." << endl;
        }
    }
}

// this is the armor menu, you can manage your armor here, you can equip it to increase your armor stat, 
// upgrade it to increase your armor stat even more, or drop it if you want to get rid of it.
// now idk how the upgrade system will work, maybe you can find armor upgrades in the sewer or buy them from the shop, 
// or maybe you can just upgrade it with gold, idk, but for now it just says you upgraded it and increases your armor stat by 5.
void armorMenu(playerType& player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n==== ARMOR MENU ====" << "\n"
            << "a. Equip Armor" << "\n"
            << "b. Upgrade Armor" << "\n"
            << "d. Drop Armor" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_a) {
            clearScreen();

            cout << "You equipped the armor!" << endl;
        }
        else if (choice == KEY_b) {
            clearScreen();

            player.armor += 5;
            cout << "You upgraded your armor! Your armor stat is now " << player.armor << endl;
        }
        else if (choice == KEY_d) {
            clearScreen();

            player.armor = 0;
            cout << "You dropped your armor!" << endl;
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            clearScreen();
            cout << "Invalid choice." << endl;
        }
    }
}

// i added this because i thought that maybe we'd need it (of course we do)
// for now its just the save and load functions, but we can add more to it later if we need to, 
// like maybe a function to delete the save file or something like that, but for now this is just the basic save and load functionality, 
// it saves all of the player's stats and inventory to a text file and loads them back when you want to continue your game.
// i tested it and it works ok.
void saveGame(playerType& player) {
    ofstream saveFile("savegame.txt");
    if (saveFile.is_open()) {
        saveFile << player.health << endl;
        saveFile << player.strength << endl;
        saveFile << player.armor << endl;
        saveFile << player.healthPotions << endl;
        saveFile << player.strengthPotions << endl;
        saveFile << player.swordDamage << endl;
        saveFile << player.bread << endl;
        saveFile << player.gold << endl;

        saveFile.close();
        cout << "Game saved successfully!" << endl;
    }
    else {
        cout << "Game not saved!" << endl;
    }
}
void loadGame(playerType& player) {
    ifstream loadFile("savegame.txt");
    if (loadFile.is_open()) {
        loadFile >> player.health;
        loadFile >> player.strength;
        loadFile >> player.armor;
        loadFile >> player.healthPotions;
        loadFile >> player.strengthPotions;
        loadFile >> player.swordDamage;
        loadFile >> player.bread;
        loadFile >> player.gold;
        loadFile.close();

        cout << "Game loaded successfully!" << endl;
    }
    else {
        cout << "No saved game was found!" << endl;
    }
}
