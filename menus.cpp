/*
Alir Louis

Contains all the menu UI and some logic for the menus

Functions:
menuHandler() : Redirects player to the proper menu
signHandler() : Print the appropriate sign text to the top of the screen
mainMenu()
helpMenu()
inventoryMenu()
statsMenu()
shopMenu()
potionMenu()
breadMenu()

deathMenu()
winMenu()
*/

#include <iostream>
#include <conio.h>	// Keyboard handling
#include <string>

#include "defs.h"
#include "structs.h"
#include "prototypes.h"

using namespace std;


int breadHealing = 1;

int shopHealthPotionPrice = 10;
int shopStrengthPotionPrice = 15;
int shopBreadPrice = 5;
int shopHealthPotionsStock = 5;
int shopStrengthPotionsStock = 3;
int shopBreadStock = 10;

void menuHandler(string (*map)[2][MAP_HEIGHT][MAP_WIDTH], playerType &player, vector<Enemy*>& enemies, string &object) {
    if      (object == SHOP)            { shopMenu(player); }
    elif    (object == ENTERANCE) { object = "";  loadLevel(map, player, enemies); }
    elif    (object == SIGN)            { signHandler(player); }
}

void signHandler(playerType& player) {
    string stage = player.stage;
    int sublevel = player.sublevel;

    if (stage == "SEWER" && sublevel == 1) { message("Beware of rats, slime, and other dangers below."); }
}

void mainMenu(playerType &player) {
    int choice = 0;

    while (choice != '5') {
        clearScreen();

        cout << "\n\n==== TEXT ROGUELIKE ====" << "\n"
            << "1. Start Game" << "\n"
            << "2. Load Game" << "\n"
            << "3. Save Game" << "\n"
            << "4. Help" << "\n"
            << "5. Save & Exit" << "\n"
            << "6. Exit Without Saving" << endl;

        choice = _getch();

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
            clearScreen();
            showCursor();
            exit(0);
        }
        else if (choice == KEY_6) {
            te_error("Are you sure you want to exit without saving? y/N");
            if (_getch() == KEY_y) {
                clearScreen();
                showCursor();
                exit(0);
            }
        }
        else {
            cout << "Invalid choice. Please select a number 1-5." << flush;
        }
    }
}

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
            << "Arrow Keys: Move your character cardinally" << "\n"
            << "HOME, END, PgUp, PgDn: Move your character intercardinally"
            << "e: Eat bread" << "\n"
            << "i: Open inventory" << "\n"
            << "/: Open help menu" << "\n"
            << "SPACE: Advance Text" << flush;
        more();
        clearScreen();
        cout << "\n\n==== MENUS ====" << "\n"
            << "In the inventory menu, you can manage your potions and bread." << "\n"
            << "In the stats menu, you can view your current health, strength, armor, and how many potions you have." << "\n"
            << "In the shop menu, you can buy health potions, strength potions, and bread." << "\n"
            << "In the potion menu, you can drink your health and strength potions to increase your stats." << "\n"
            << "\n==== SAVE / LOAD ====" << "\n"
            << "You can save your game from the main menu and load it later to continue your adventure." << "\n"
            << "Good luck, and have fun playing!" << "\n"
            << "\nESC. Back" << flush;

        while ((choice = _getch()) != KEY_ESC) { te_print("Invalid choice. Press ESC to exit."); }
    }
}

// this is the inventory menu, you can manage your potions, sword, bread, and armor here, you can also view how many of each item you have
void inventoryMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== INVENTORY ====" << "\n"
            << "a. Potions (" << player.healthPotions + player.strengthPotions << " total)" << "\n"
            << "b. Bread (" << player.bread << " left)" << "\n"
            << "ESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_a) {
            potionMenu(player);
            clearScreen();
        }
        else if (choice == KEY_b) {
            breadMenu(player);
            clearScreen();
        }
        else if (choice == KEY_ESC) {
            clearScreen();
        }
        else {
            te_print("Invalid choice. Please select a letter a-d");
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
            << "Health Potions: " << player.healthPotions << "\n"
            << "Strength Potions: " << player.strengthPotions << "\n"
            << "Bread: " << player.bread << "\n"
            << "Gold: " << player.gold << "\n"
            << "Level: " << player.stage << "-" << player.sublevel - 1 << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_ESC) {
            clearScreen();
        }
        else {
            te_print("Invalid choice.");
        }

    }
}

// this is the shop menu, you can buy health potions, strength potions, and bread here, the prices and stock are displayed, if you don't have enough gold or if the item is out of stock it will let you know!.
void shopMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\033[3H";
        cout << "Welcome to the shop!" << "\n\n"
            << "a. Buy Health Potion (" << shopHealthPotionPrice << " gold) " << shopHealthPotionsStock << " left" << "\n"
            << "b. Buy Strength Potion (" << shopStrengthPotionPrice << " gold) " << shopStrengthPotionsStock << " left" << "\n"
            << "c. Buy Bread (" << shopBreadPrice << " gold) " << shopBreadStock << " left" << "\n"
            << "\nYour gold: " << player.gold << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_a) {
            if (shopHealthPotionsStock > 0) {
                if (player.gold >= shopHealthPotionPrice) {
                    te_print("You purchased a Health Potion.");
                    player.healthPotions += 1;
                    shopHealthPotionsStock -= 1;
                    player.gold -= shopHealthPotionPrice;
                }
                else {
                    te_print("You don't have enough gold to buy a Health Potion!");
                }
            }
            else {
                te_print("No Health Potions left. We are out of stock, sorry!");
            }
        }
        else if (choice == KEY_b) {
            if (shopStrengthPotionsStock > 0) {
                if (player.gold >= shopStrengthPotionPrice) {
                    te_print("You purchased a Strength Potion.");
                    player.strengthPotions += 1;
                    shopStrengthPotionsStock -= 1;
                    player.gold -= shopStrengthPotionPrice;
                }
                else {
                    te_print("You don't have enough gold to buy a Strength Potion!");
                }
            }
            else {
                te_print("No Strength Potions left. We are out of stock, sorry!");
            }
        }
        else if (choice == KEY_c) {
            if (shopBreadStock > 0) {
                if (player.gold >= shopBreadPrice) {
                    te_print("You purchased one Bread.");
                    player.bread += 1;
                    shopBreadStock = shopBreadStock - 1;
                    player.gold -= shopBreadPrice;
                }
                else {
                    te_print("You don't have enough gold to buy Bread!");
                }
            }
            else {
                te_print("No Bread left. We are out of stock, sorry! ");
            }
        }
        else if (choice == KEY_ESC) {
            clearScreen();
        }
        else {
            te_print("Invalid choice.");
        }
    }
}

void potionMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\033[3H";
        cout << "==== POTION MENU ====" << "\n"
            << CLEAR_LINE << "a. Health Potion (" << player.healthPotions << " left)" << "\n"
            << CLEAR_LINE << "b. Strength Potion (" << player.strengthPotions << " left)" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_a) {
            if (player.healthPotions > 0) {
                if (player.health < player.maxHealth) {
                    healPlayer(player, rollDie(8));
                    player.healthPotions -= 1;
                    te_print("You drank a Health Potion. Health is now " + to_string(player.health) + ".");

                    if (player.healthPotions == 0) {
                        more();
                        te_print("You no longer have any Health Potions left!");
                    }
                }
                else {
                    te_print("You are at max health!");
                }
            }
            else {
                te_print("You have no Health Potions left!");
            }
        }
        else if (choice == KEY_b) {
            if (player.strengthPotions > 0) {
                player.strength += rollDie(4);
                player.strengthPotions -= 1;

                te_print("You drank a Strength Potion. Strength is now " + to_string(player.strength) + ".");

                if (player.strengthPotions == 0) {
                    more();
                    te_print("You no longer have any Strength Potions left!");
                }
            }
            else {
                te_print("You have no Strength Potions left!");
            }
        }
        else if (choice == KEY_ESC) {
            clearScreen();
        }
        else {
            te_print("Invalid choice.");
        }
    }
}

void breadMenu(playerType &player) {
    clearScreen();

    int choice = 0;

    while (choice != KEY_ESC) {
        cout << "\n\n==== BREAD MENU ====" << "\n"
            << "a. Eat Bread (" << player.bread << " left)" << "\n"
            << "\nESC. Back" << endl;

        choice = _getch();

        if (choice == KEY_a) {
            if (player.bread > 0) {
                if (player.health < player.maxHealth) {
                    player.health += breadHealing;
                    player.bread -= 1;

                    te_print("You ate the bread. Health is now " + to_string(player.health) + ".");

                    if (player.bread == 0) {
                        more();
                        te_print("You no longer have any bread left!");
                    }
                }
                else {
                    te_print("You are at max health!");
                }
            }
            else {
                te_print("You have no bread left!");
            }
        }
        else if (choice == KEY_ESC) {
            clearScreen();
        }
        else {
            cout << CLEAR_LINE << "Invalid choice." << flush;
        }
    }
}

//Alir Louis 4/28/26
// Shows when the player dies.
// This is my death screen for the roguelike project.
void deathMenu(playerType& player) {
    clearScreen();

    cout << "\033[3H";
    cout << "=====================================\n"
        << "              GAME OVER              \n"
        << "=====================================\n\n";

    cout << "              ___________\n"
        << "             /           \\\n"
        << "            /   R. I. P.  \\\n"
        << "           |               |\n"
        << "           |   HERE LIES   |\n"
        << "           |  THE PLAYER   |\n"
        << "           |               |\n"
        << "           |   GAME OVER   |\n"
        << "           |_______________|\n"
        << "              / / / / / /\n"
        << "             /_/ /_/ /_/\n\n";

    cout << "The grave is quiet...\n"
        << "Another adventurer has fallen.\n\n";

    cout << "Final Stats:\n"
        << "Level: " << player.level << "\n"
        << "XP: " << player.xp << "\n"
        << "Stage: " << player.stage << "-" << player.sublevel-1 << "\n"
        << "Gold: " << player.gold << "\n"
        << "Total Points: " << player.level + player.gold + player.healthPotions + player.strengthPotions + (player.xp / 2) << "\n\n";

    cout << "Press SPACE to end game." << endl;

    while (_getch() != KEY_SPACE) {
        te_print("Press SPACE to exit.");
    }

    clearScreen();
    showCursor();
    exit(0);
}

// Alir Louis 4/28/26
// Shows when the player wins the game.
// this is the Victory screen for the winning kill
void winMenu(playerType& player) {
    clearScreen();

    cout << "\033[3H";
    cout << "=====================================\n"
        << "              A Hero's Return        \n"
        << "=====================================\n";
    cout << "               \\  |  /\n"
        << "             ---  *  ---\n"
        << "               /  |  \\\n"
        << "             ___________\n"
        << "            '._==_==_=_.'\n"
        << "            .-\\:      /-.\n"
        << "           | (|:.     |) |\n"
        << "            '-|:.     |-'\n"
        << "              \\::.    /\n"
        << "               '::. .'\n"
        << "                 ) (\n"
        << "               _.' '._\n"
        << "              `-------`\n\n";

    cout << "          V I C T O R Y ! ! !      \n";
    cout << "The town is saved!\n"
        << "The hero returns home, victorious from their adventure.\n\n";

    cout << "Final Stats:\n"
        << "Level: " << player.level << "\n"
        << "XP: " << player.xp << "\n"
        << "Gold: " << player.gold << "\n"
        << "Total Points: " << player.level + player.gold + player.healthPotions + player.strengthPotions + (player.xp / 2) << "\n\n";

    cout << "Press SPACE to end game." << endl;
    while (_getch() != KEY_SPACE) {
        te_print("Press SPACE to exit.");
    }

    clearScreen();
    showCursor();
    exit(0);
}
