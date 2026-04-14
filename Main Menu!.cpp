#include <iostream>
#include <string>
#include <fstream>
// Let me know if you want me to add any more libraries, but for now these are the ones i think we need for the basic functionality of the game,
//ALSO, I THINK THIS IS IMPORTANT BUT I USED A LOT OF GLOBAL VARIABLES FOR THE PLAYER STATS AND INVENTORY, I KNOW THIS IS NOT THE BEST PRACTICE BUT IT WAS EASIER FOR ME TO IMPLEMENT THE SAVE AND LOAD FUNCTIONALITY THIS WAY,
// AND I USED CHAR INSTEAD OF INT BECAUSE WHENEVER A PLAYER ADDED THE WRONG LETTER IT WOULD CAUSE AN INFINITE LOOP, I THINK THIS IS A GOOD SOLUTION TO THAT PROBLEM, 
// BUT IF YOU WANT ME TO CHANGE IT TO INT OR SOMETHING ELSE JUST LET ME KNOW AND I CAN DO THAT, I THINK.

using namespace std;
// if the numbers need to be changed, change them here and it will change everywhere in the code (at least i think it should?)
int health = 100;
int strength = 10;
int armor = 25;
int healthPotions = 10;
int strengthPotions = 5;
int swordDamage = 10;
int breadHealing = 5;
int bread = 5;

// again these can be changed here and it will change everywhere in the code...i think, these are just testing numbers for the shop, they can be changed to whatever you want
int shopHealthPotionPrice = 10;
int shopStrengthPotionPrice = 15;
int shopBreadPrice = 5;
int shopHealthPotionsStock = 5;
int shopStrengthPotionsStock = 3;
int shopBreadStock = 10;
int gold = 100;
//im pretty new to this, my fault if it aint too advanced or clean
//im learning as i go, but this is just the basic structure of the game, we can add more features and functionality later on, 
// lemme know if this is too much or there's a better way to do this.
void mainMenu();
void townMenu();
void helpMenu();
void saveGame();
void loadGame();
void inventoryMenu();
void statsMenu();
void shopMenu();
void breadMenu();
void potionMenu();
void swordMenu();
void armorMenu();
void sewerMenu();
// again sorry if this is all over the place im kinda learning as i go, but i wanted to get something down and then build on it, so this is just the basic structure of the game,
//  for now you can just explore the town and manage your inventory and stats
int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    char choice = ' ';

    while (choice != '5') {
        cout << "\n==== TEXT ROGUELIKE ====" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Load Game" << endl;
        cout << "3. Save Game" << endl;
        cout << "4. Help" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == '1') {
            townMenu();
        }
        else if (choice == '2') {
            loadGame();
        }
        else if (choice == '3') {
            saveGame();
        }
        else if (choice == '4') {
			helpMenu();
        }
        else if (choice == '5') {
            saveGame();
            cout << "Run saved, Exiting the world..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
// of course the help menu. i placed some placeholder text in there for now, but we can change it to whatever we want, 
// this is just to give the player some information about the game and how to play it,
void helpMenu() {
    char choice = ' ';

    while (choice != 'x') {
        cout << "\n==== HELP ====" << endl;
        cout << "This is a text-based roguelike game. Survive and save the town!" << endl;
        cout << "\n==== PLANNED CONTROLS ====" << endl;
        cout << "Arrow Keys: Move your character" << endl;
        cout << "I: Open inventory" << endl;
        cout << "Space: Advance text" << endl;
        cout << "\n==== MENUS ====" << endl;
        cout << "In the town menu, you can go to the sewer, visit the shop, check your inventory, or view your stats." << endl;
        cout << "In the inventory menu, you can manage your potions, sword, bread, and armor." << endl;
        cout << "In the stats menu, you can view your current health, strength, armor, and how many potions you have." << endl;
        cout << "In the shop menu, you can buy health potions, strength potions, and bread." << endl;
        cout << "In the potion menu, you can drink your health and strength potions to increase your stats." << endl;
        cout << "In the sword menu, you can equip, upgrade, or drop your sword." << endl;
        cout << "In the armor menu, you can equip, upgrade, or drop your armor." << endl;
        cout << "\n==== SAVE / LOAD ====" << endl;
        cout << "You can save your game from the main menu and load it later to continue your adventure." << endl;
        cout << "Good luck, and have fun playing!" << endl;
        cout << "\nx. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 'x') {
            cout << "Returning to main menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}

// this is the main menu for the town, you can go to the sewer, visit the shop, check your inventory, or view your stats
void townMenu() {
    char choice = ' ';

    while (choice != '5') {
        cout << "\n==== TOWN MENU ====" << endl;
        cout << "1. Go to Sewer" << endl;
        cout << "2. Visit Shop" << endl;
        cout << "3. Check Inventory" << endl;
        cout << "4. View Stats" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == '1') {
			sewerMenu();
        }
        else if (choice == '2') {
            shopMenu();
        }
        else if (choice == '3') {
            inventoryMenu();
        }
        else if (choice == '4') {
            statsMenu();
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
void inventoryMenu() {
    char choice = ' ';

    while (choice != 'x') {
        cout << "\n==== INVENTORY ====" << endl;
        cout << "a. Potions (" << healthPotions + strengthPotions << " total)" << endl;
        cout << "b. Sword" << endl;
        cout << "c. Bread (" << bread << " left)" << endl;
        cout << "d. Armor" << endl;
        cout << "x. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 'a') {
            potionMenu();
        }
        else if (choice == 'b') {
            swordMenu();
        }
        else if (choice == 'c') {
            breadMenu();
        }
        else if (choice == 'd') {
            armorMenu();
        }
        else if (choice == 'x') {
            cout << "Returning to town menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
// this is the stats menu, you can view your current health, strength, armor, and how many potions you have, as well as your sword damage and how much gold you have!.
void statsMenu() {
    char choice = ' ';
    while (choice != 'x') {
        cout << "\n==== STATS ====" << endl;
        cout << "Health: " << health << endl;
        cout << "Strength: " << strength << endl;
        cout << "Armor: " << armor << endl;
        cout << "Health Potions: " << healthPotions << endl;
        cout << "Strength Potions: " << strengthPotions << endl;
        cout << "Sword Damage: " << swordDamage << endl;
        cout << "Bread: " << bread << endl;
        cout << "Gold: " << gold << endl;
        cout << "x. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 'x') {
            cout << "Returning to town menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }

    }
}
// this is the shop menu, you can buy health potions, strength potions, and bread here, the prices and stock are displayed, if you don't have enough gold or if the item is out of stock it will let you know!.
void shopMenu() {
    char choice = ' ';

    while (choice != 'x') {
        cout << "\nWelcome to the shop!" << endl;
        cout << "a. Buy Health Potion (" << shopHealthPotionPrice << " gold) " << shopHealthPotionsStock << " left" << endl;
        cout << "b. Buy Strength Potion (" << shopStrengthPotionPrice << " gold) " << shopStrengthPotionsStock << " left" << endl;
        cout << "c. Buy Bread (" << shopBreadPrice << " gold) " << shopBreadStock << " left" << endl;
        cout << "Your gold: " << gold << endl;
        cout << "x. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 'a') {
            if (shopHealthPotionsStock > 0) {
                if (gold >= shopHealthPotionPrice) {
                    cout << "You purchased a Health Potion." << endl;
                    healthPotions = healthPotions + 1;
                    shopHealthPotionsStock = shopHealthPotionsStock - 1;
                    gold = gold - shopHealthPotionPrice;
                }
                else {
                    cout << "You don't have enough gold to buy a Health Potion!" << endl;
                }
            }
            else {
                cout << "No Health Potions left. We are out of stock, sorry!" << endl;
            }
        }
        else if (choice == 'b') {
            if (shopStrengthPotionsStock > 0) {
                if (gold >= shopStrengthPotionPrice) {
                    cout << "You purchased a Strength Potion." << endl;
                    strengthPotions = strengthPotions + 1;
                    shopStrengthPotionsStock = shopStrengthPotionsStock - 1;
                    gold = gold - shopStrengthPotionPrice;
                }
                else {
                    cout << "You don't have enough gold to buy a Strength Potion!" << endl;
                }
            }
            else {
                cout << "No Strength Potions left. We are out of stock, sorry!" << endl;
            }
        }
        else if (choice == 'c') {
            if (shopBreadStock > 0) {
                if (gold >= shopBreadPrice) {
                    cout << "You purchased some Bread." << endl;
                    bread = bread + 1;
                    shopBreadStock = shopBreadStock - 1;
                    gold = gold - shopBreadPrice;
                }
                else {
                    cout << "You don't have enough gold to buy Bread!" << endl;
                }
            }
            else {
                cout << "No Bread left. We are out of stock, sorry! " << endl;
            }
        }
        else if (choice == 'x') {
            cout << "Returning to town menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
// this is the sewer menu, you can enter the sewer to explore and find new items and enemies, 
// you can also search the area to find hidden items or read the warning sign to get some information about the dangers that lurk in the sewer.
void sewerMenu() {
    char choice = ' ';

    while (choice != 'x') {
        cout << "\n==== SEWER MENU ====" << endl;
        cout << "a. Enter Sewer" << endl;
        cout << "b. Search Area" << endl;
        cout << "c. Read Warning Sign" << endl;
        cout << "x. Back" << endl;
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
void potionMenu() {
    char choice = ' ';

    while (choice != 'x') {
        cout << "\n==== POTION MENU ====" << endl;
        cout << "a. Health Potion (" << healthPotions << " left)" << endl;
        cout << "b. Strength Potion (" << strengthPotions << " left)" << endl;
        cout << "x. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 'a') {
            if (healthPotions > 0) {
                health = health + 10;
                healthPotions = healthPotions - 1;
                cout << "You drank a Health Potion. Health is now " << health << "." << endl;

                if (healthPotions == 0) {
                    cout << "You no longer have any Health Potions left!" << endl;
                }
            }
            else {
                cout << "You have no Health Potions left!" << endl;
            }
        }
        else if (choice == 'b') {
            if (strengthPotions > 0) {
                strength = strength + 5;
                strengthPotions = strengthPotions - 1;
                cout << "You drank a Strength Potion. Strength is now " << strength << "." << endl;

                if (strengthPotions == 0) {
                    cout << "You no longer have any Strength Potions left!" << endl;
                }
            }
            else {
                cout << "You have no Strength Potions left!" << endl;
            }
        }
        else if (choice == 'x') {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
void breadMenu() {
    char choice = ' ';

    while (choice != 'x') {
        cout << "\n==== BREAD MENU ====" << endl;
        cout << "a. Eat Bread" << endl;
        cout << "b. Drop Bread" << endl;
        cout << "x. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 'a') {
            if (bread > 0) {
                health = health + breadHealing;
                bread = bread - 1;
                cout << "You ate the bread. Health is now " << health << "." << endl;

                if (bread == 0) {
                    cout << "You no longer have any bread left!" << endl;
                }
            }
            else {
                cout << "You have no bread left!" << endl;
            }
        }
        else if (choice == 'b') {
            if (bread > 0) {
                bread = bread - 1;
                cout << "You dropped the bread!" << endl;

                if (bread == 0) {
                    cout << "You no longer have any bread left!" << endl;
                }
            }
            else {
                cout << "You have no bread left!" << endl;
            }
        }
        else if (choice == 'x') {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
// this is the sword menu, you can manage your sword here, you can equip it to increase your strength, upgrade it to increase your sword damage, or drop it if you want to get rid of it.
// if you drop it you will have to find another one in the sewer or buy one from the shop!
void swordMenu() {
    char choice = ' ';

    while (choice != 'x') {
        cout << "\n==== SWORD MENU ====" << endl;
        cout << "a. Equip Sword" << endl;
        cout << "b. Upgrade Sword" << endl;
        cout << "d. Drop Sword" << endl;
        cout << "x. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 'a') {
            cout << "You equipped the sword!" << endl;
        }
        else if (choice == 'b') {
            cout << "You upgraded your sword!" << endl;
        }
        else if (choice == 'd') {
            cout << "You dropped your sword!" << endl;
        }
        else if (choice == 'x') {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
// this is the armor menu, you can manage your armor here, you can equip it to increase your armor stat, 
// upgrade it to increase your armor stat even more, or drop it if you want to get rid of it.
// now idk how the upgrade system will work, maybe you can find armor upgrades in the sewer or buy them from the shop, 
// or maybe you can just upgrade it with gold, idk, but for now it just says you upgraded it and increases your armor stat by 5.
void armorMenu() {
    char choice = ' ';
    while (choice != 'x') {
        cout << "\n==== ARMOR MENU ====" << endl;
        cout << "a. Equip Armor" << endl;
        cout << "b. Upgrade Armor" << endl;
        cout << "d. Drop Armor" << endl;
        cout << "x. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 'a') {
            cout << "You equipped the armor!" << endl;
        }
        else if (choice == 'b') {
            cout << "You upgraded your armor!" << endl;
        }
        else if (choice == 'd') {
            cout << "You dropped your armor!" << endl;
        }
        else if (choice == 'x') {
            cout << "Returning to inventory menu..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}
// i added this because i thought that maybe we'd need it (of course we do)
// for now its just the save and load functions, but we can add more to it later if we need to, 
// like maybe a function to delete the save file or something like that, but for now this is just the basic save and load functionality, 
// it saves all of the player's stats and inventory to a text file and loads them back when you want to continue your game.
// i tested it and it works ok.
void saveGame() {
    ofstream saveFile("savegame.txt");
    if (saveFile.is_open()) {
        saveFile << health << endl;
        saveFile << strength << endl;
        saveFile << armor << endl;
        saveFile << healthPotions << endl;
        saveFile << strengthPotions << endl;
        saveFile << swordDamage << endl;
        saveFile << bread << endl;
        saveFile << gold << endl;

        saveFile.close();
        cout << "Game saved successfully!" << endl;
    }
    else {
        cout << "Game not saved!" << endl;
    }
}
void loadGame() {
    ifstream loadFile("savegame.txt");
    if (loadFile.is_open()) {
        loadFile >> health;
        loadFile >> strength;
        loadFile >> armor;
        loadFile >> healthPotions;
        loadFile >> strengthPotions;
        loadFile >> swordDamage;
        loadFile >> bread;
        loadFile >> gold;
        loadFile.close();

        cout << "Game loaded successfully!" << endl;
    }
    else {
        cout << "No saved game was found!" << endl;
    }
}
