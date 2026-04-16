/*
Alir Louis

Functions:
menuHandler(): Redirects player to the proper menu
mainMenu()
helpMenu()
inventoryMenu()
statsMenu()
shopMenu()
sewerMenu(): Gonna remove once I get the sewer up and running
potionMenu()
breadMenu()
swordMenu()
armorMenu()
*/

#include <iostream>
#include <conio.h>	// Keyboard handling
#include <string>

#include "defs.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;


int breadHealing = 5;

// If any default player data needs to be changed, it should be done in initializePlayer(). 
// If a new player stat needs to be added, add it in playerType in structs.h and initialize it in initializePlayer()

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

void menuHandler(string (*map)[MAP_HEIGHT][MAP_WIDTH], playerType &player, string &object) {
    if      (object == SHOP)            { shopMenu(player); }
    elif    (object == SEWER_ENTERANCE) { object = "";  generateSewer(map, player); }
    elif    (object == SIGN)            { signHandler(player); }
}

void signHandler(playerType& player) {
    string level = player.level;

    if (level == "SEWER_1") { te_print("Beware of rats, slime, and other dangers below."); }
    wait();
}

void mainMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != '5') {
        cout << "\n\n==== TEXT ROGUELIKE ====" << "\n"
            << "1. Start Game" << "\n"
            << "2. Load Game" << "\n"
            << "3. Save Game" << "\n"
            << "4. Help" << "\n"
            << "5. Exit" << endl;

        choice = _getch();
        clearScreen();

        if (choice == '1') {
            break;  // Return to the function that called this to either start a new game or continue game in progress
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
            te_print("Run saved. Exiting world...");
            cout << endl;
            exit(1);
        }
        else {
            cout << "Invalid choice. Please select a number 1-5." << flush;
        }
    }
}

// of course the help menu. i placed some placeholder text in there for now, but we can change it to whatever we want, 
// this is just to give the player some information about the game and how to play it,
void helpMenu() {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== HELP ====" << "\n"
            << "This is a text-based roguelike game. Survive and save the town!" << flush;
        more();
        clearScreen();
        cout << "\n\n==== CONTROLS ====" << "\n"
            << "Arrow Keys: Move your character" << "\n"
            << "7: Move North West" << "\n"
            << "9: Move North East" << "\n"
            << "1: Move South West" << "\n"
            << "3: Move South East" << "\n"
            << "e: Eat bread" << "\n"
            << "i: Open inventory" << "\n"
            << "/: Open help menu" << "\n"
            << "SPACE: Advance Text or Menu" << flush;
        more();
        clearScreen();
        cout << "\n\n==== MENUS ====" << "\n"
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
            << "\nESC. Back" << flush;

        while ((choice = _getch()) != KEY_ESC) { te_print("Invalid choice. Press ESC to exit."); }

        cout << "Returning to main menu..." << endl;
    }
}

// this is the inventory menu, you can manage your potions, sword, bread, and armor here, you can also view how many of each item you have
void inventoryMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== INVENTORY ====" << "\n"
            << "a. Potions (" << player.healthPotions + player.strengthPotions << " total)" << "\n"
            << "b. Sword" << "\n"
            << "c. Bread (" << player.bread << " left)" << "\n"
            << "d. Armor" << "\n"
            << "ESC. Back" << endl;

        choice = _getch();
        clearScreen();

        if (choice == KEY_a) {
            potionMenu(player);
            clearScreen();
        }
        else if (choice == KEY_b) {
            swordMenu(player);
            clearScreen();
        }
        else if (choice == KEY_c) {
            breadMenu(player);
            clearScreen();
        }
        else if (choice == KEY_d) {
            armorMenu(player);
            clearScreen();
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to level..." << endl;
        }
        else {
            cout << "Invalid choice. Please select a letter a-d" << flush;
        }
    }
}
// this is the stats menu, you can view your current health, strength, armor, and how many potions you have, as well as your sword damage and how much gold you have!.
void statsMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== STATS ====" << "\n"
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
        clearScreen();

        if (choice == KEY_ESC) {
            cout << "Returning to town menu..." << endl;
        }
        else {
            cout << "Invalid choice." << flush;
        }

    }
}
// this is the shop menu, you can buy health potions, strength potions, and bread here, the prices and stock are displayed, if you don't have enough gold or if the item is out of stock it will let you know!.
void shopMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\nWelcome to the shop!" << "\n\n"
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
                    cout << "You purchased a Health Potion." << flush;
                    player.healthPotions += 1;
                    shopHealthPotionsStock -= 1;
                    player.gold -= shopHealthPotionPrice;
                }
                else {
                    cout << "You don't have enough gold to buy a Health Potion!" << flush;
                }
            }
            else {
                cout << "No Health Potions left. We are out of stock, sorry!" << flush;
            }
        }
        else if (choice == KEY_b) {
            if (shopStrengthPotionsStock > 0) {
                if (player.gold >= shopStrengthPotionPrice) {
                    cout << "You purchased a Strength Potion." << flush;
                    player.strengthPotions += 1;
                    shopStrengthPotionsStock -= 1;
                    player.gold -= shopStrengthPotionPrice;
                }
                else {
                    cout << "You don't have enough gold to buy a Strength Potion!" << flush;
                }
            }
            else {
                cout << "No Strength Potions left. We are out of stock, sorry!" << flush;
            }
        }
        else if (choice == KEY_c) {
            if (shopBreadStock > 0) {
                if (player.gold >= shopBreadPrice) {
                    cout << "You purchased one Bread." << flush;
                    player.bread += 1;
                    shopBreadStock = shopBreadStock - 1;
                    player.gold -= shopBreadPrice;
                }
                else {
                    cout << "You don't have enough gold to buy Bread!" << flush;
                }
            }
            else {
                cout << "No Bread left. We are out of stock, sorry! " << flush;
            }
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to town menu..." << endl;
        }
        else {
            cout << "Invalid choice." << flush;
        }
    }
}

// this is the sewer menu, you can enter the sewer to explore and find new items and enemies, 
// you can also search the area to find hidden items or read the warning sign to get some information about the dangers that lurk in the sewer.
void sewerMenu(playerType &player) {
    te_print("You enter the sewer, the domain of filth. It is dark, damp, and full of danger lurking below.");
}

// this is the potion menu, same as the other menus, you can manage your potions here etc etc. . .
// Dustin 4/15: I know the implementation of all the ansi stuff is dirty, but it's the best way I could find to make it do what it needed to do
void potionMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== POTION MENU ====" << "\n"
            << CLEAR_LINE <<"a. Health Potion (" << player.healthPotions << " left)" << "\n"
            << CLEAR_LINE << "b. Strength Potion (" << player.strengthPotions << " left)" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();
        cout << CURSOR_HOME;

        if (choice == KEY_a) {
            if (player.healthPotions > 0) {
                player.health += 10;
                player.healthPotions -= 1;
                cout << CLEAR_LINE << "You drank a Health Potion. Health is now " << player.health << ".";

                if (player.healthPotions == 0) {
                    more();
                    cout << CURSOR_HOME << CLEAR_LINE << "You no longer have any Health Potions left!";
                }

                cout << flush;
            }
            else {
                cout << CLEAR_LINE << "You have no Health Potions left!" << flush;
            }
        }
        else if (choice == KEY_b) {
            if (player.strengthPotions > 0) {
                player.strength += 5;
                player.strengthPotions -= 1;

                cout << CLEAR_LINE << "You drank a Strength Potion. Strength is now " << player.strength << ".";

                if (player.strengthPotions == 0) {
                    more();
                    cout << CURSOR_HOME << CLEAR_LINE <<  "You no longer have any Strength Potions left!";
                }

                cout << flush;
            }
            else {
                cout << CLEAR_LINE << "You have no Strength Potions left!" << flush;
            }
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to inventory menu..." << endl;
            clearScreen();
        }
        else {
            cout << CLEAR_LINE << "Invalid choice." << flush;
        }
    }
}

void breadMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== BREAD MENU ====" << "\n"
            << "a. Eat Bread" << "\n"
            << "d. Drop Bread" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();
        cout << CURSOR_HOME;

        if (choice == KEY_a) {
            if (player.bread > 0) {
                player.health += breadHealing;
                player.bread -= 1;

                cout << CLEAR_LINE << "You ate the bread. Health is now " << player.health << ".";

                if (player.bread == 0) {
                    more();
                    te_print("You no longer have any bread left!");
                }

                cout << flush;
            }
            else {
                cout << CLEAR_LINE << "You have no bread left!" << flush;
            }
        }
        else if (choice == KEY_d) {
            if (player.bread > 0) {
                player.bread -= 1;

                cout << CLEAR_LINE << "You dropped the bread!" << flush;

                if (player.bread == 0) {
                    more();
                    te_print("You no longer have any bread left!");
                }
            }
            else {
                cout << CLEAR_LINE << "You have no bread left!" << flush;
            }
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to inventory menu..." << endl;
            clearScreen();
        }
        else {
            cout << CLEAR_LINE << "Invalid choice." << flush;
        }
    }
}

// this is the sword menu, you can manage your sword here, you can equip it to increase your strength, upgrade it to increase your sword damage, or drop it if you want to get rid of it.
// if you drop it you will have to find another one in the sewer or buy one from the shop!
void swordMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== SWORD MENU ====" << "\n"
            << "a. Equip Sword" << "\n"
            << "b. Upgrade Sword" << "\n"
            << "d. Drop Sword" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();
        cout << CURSOR_HOME;

        if (choice == KEY_a) {
            cout << CLEAR_LINE;
            cout << "You equipped the sword!" << endl;
        }
        else if (choice == KEY_b) {
            cout << CLEAR_LINE;
            cout << "You upgraded your sword!" << endl;
        }
        else if (choice == KEY_d) {
            cout << CLEAR_LINE;
            cout << "You dropped your sword!" << endl;
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            cout << CLEAR_LINE << "Invalid choice." << endl;
        }
    }
}

// this is the armor menu, you can manage your armor here, you can equip it to increase your armor stat, 
// upgrade it to increase your armor stat even more, or drop it if you want to get rid of it.
// now idk how the upgrade system will work, maybe you can find armor upgrades in the sewer or buy them from the shop, 
// or maybe you can just upgrade it with gold, idk, but for now it just says you upgraded it and increases your armor stat by 5.
void armorMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== ARMOR MENU ====" << "\n"
            << "a. Equip Armor" << "\n"
            << "b. Upgrade Armor" << "\n"
            << "d. Drop Armor" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();
        cout << CURSOR_HOME;

        if (choice == KEY_a) {
            cout << CLEAR_LINE;
            cout << "You equipped the armor!" << endl;
        }
        else if (choice == KEY_b) {
            player.armor += 5;
            cout << CLEAR_LINE << "You upgraded your armor! Your armor stat is now " << player.armor << endl;
        }
        else if (choice == KEY_d) {
            player.armor = 0;
            cout << CLEAR_LINE << "You dropped your armor!" << endl;
        }
        else if (choice == KEY_ESC) {
            cout << "Returning to inventory menu..." << endl;
            clearScreen();
        }
        else {
            cout << CLEAR_LINE << "Invalid choice." << endl;
        }
    }
}
