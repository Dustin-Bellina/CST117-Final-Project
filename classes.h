#ifndef CLASSES_H
#define CLASSES_H

/*
Armani Ruffin

Contains the enemy classes and data
*/

#include <string>
#include "prototypes.h"

class Enemy {
protected:
    int health, damage, ac, experience, x, y;
    bool aggro;
    std::string name;
    std::string symbol;

public:
    Enemy(int incomingHealth, int incomingDamage, int incomingAC, int incomingExperience, std::string incomingName, std::string incomingSymbol) {
        health = incomingHealth;
        damage = incomingDamage;
        ac = incomingAC;
        experience = incomingExperience;

        name = incomingName;
        symbol = incomingSymbol;

        aggro = false;

        x = 0;
        y = 0;
    }

    void setHealth(int incomingHealth) { health = incomingHealth; }
    int  getHealth() { return health; }

    int  getDamage() { return damage; }

    int  getXp() { return experience; }
    int  getAC() { return ac; }

    std::string getName() { return name; }
    std::string getSymbol() { return symbol; }

    void takeDamage(int amt) { health -= amt; }
    bool isAlive() { return health > 0; }

    void setAggro(bool val) { aggro = val; }
    bool getAggro() { return aggro; }

    void setXY(int incomingX, int incomingY) {
        x = incomingX;
        y = incomingY;
    }
    int getX() { return x; }
    int getY() { return y; }
};

// Sewer
class Rat : public Enemy {  // Sewer | Avg HP: 5 | Avg DMG: 5
    public:
        Rat() : Enemy(rollDie(4, 2), rollDie(4, 2), 8, 25, "Rat", "R") {}
};

class Slime : public Enemy {    // Sewer | Avg HP: 7 | Avg DMG: 4.5
    public:
        Slime() : Enemy(rollDie(6, 2), rollDie(4) + 2, 10, 50, "Slime", "S") {}
};

class SewerGoblin : public Enemy {  // Sewer | Avg HP: 10.5 | Avg DMG: 5.5
    public:
        SewerGoblin() : Enemy(rollDie(6, 3), rollDie(6) + 2, 12, 50, "Goblin", "G") {}
};

class Orog : public Enemy { // Sewer BOSS | Avg HP: 42.5 | Avg DMG: 7.5
    public:
        Orog() : Enemy(rollDie(8, 5) + 20, rollDie(4, 3), 15, 450, "Orog", "\033[36mO\033[0m") {
            setAggro(true);
        }
};

// Cave
class Bat : public Enemy {  // Cave | Avg HP: 5 | Avg DMG: 13.5
    public:
        Bat() : Enemy(rollDie(4, 2), rollDie(8, 3), 10, 150, "Bat", "B") {}
};

class CaveGoblin : public Enemy {   // Cave | Avg HP: 22.5 | Avg DMG: 13.5
    public:
        CaveGoblin() : Enemy(rollDie(8, 5), rollDie(8, 3), 13, 250, "Goblin", "G") {}
};

class CaveOrc : public Enemy {  // Cave | Avg HP: 15 | Avg DMG: 10
    public:
        CaveOrc() : Enemy(rollDie(8, 2) + 6, rollDie(8, 2) + 1, 15, 375, "Orc", "O") {}
};

class Dragon : public Enemy {   // Cave BOSS | Avg HP: 82.5 | Avg DMG: 13
    public:
        Dragon() : Enemy(rollDie(8, 11) + 33, rollDie(8, 2) + 4, 0, 700, "Dragon", "\033[31mD\033[0m") {
            setAggro(true);
        }
};

// Forest
class Monkey : public Enemy {  // Cave | Avg HP: 5 | Avg DMG: 13.5
    public:
        Monkey() : Enemy(rollDie(4, 2), rollDie(8, 3), 10, 150, "Monkey", "M") {}
};

class Werewolf : public Enemy {   // Cave | Avg HP: 22.5 | Avg DMG: 13.5
    public:
        Werewolf() : Enemy(rollDie(8, 5), rollDie(8, 3), 13, 250, "Werewolf", "W") {}
};

class Elf : public Enemy {  // Cave | Avg HP: 15 | Avg DMG: 10
    public:
        Elf() : Enemy(rollDie(8, 2) + 6, rollDie(8, 2) + 1, 15, 375, "Elf", "E") {}
};

class Treant : public Enemy {   // Cave BOSS | Avg HP: 82.5 | Avg DMG: 13
    public:
        Treant() : Enemy(rollDie(8, 11) + 33, rollDie(8, 2) + 4, 0, 700, "Treant", "\033[32mT\033[0m") {
            setAggro(true);
        }
};

// Castle
class CastleOrc : public Enemy {  // Cave | Avg HP: 15 | Avg DMG: 13.5
    public:
        CastleOrc() : Enemy(rollDie(8, 2) + 6, rollDie(8, 3), 15, 375, "Orc", "O") {}
};

class Hobgoblin : public Enemy {   // Cave | Avg HP: 22.5 | Avg DMG: 13.5
    public:
        Hobgoblin() : Enemy(rollDie(8, 5), rollDie(8, 3), 13, 475, "Hobgoblin", "H") {}
};

class Vampire : public Enemy {  // Cave | Avg HP: 15 | Avg DMG: 10
    public:
        Vampire() : Enemy(rollDie(8, 2) + 6, rollDie(8, 2) + 1, 15, 600, "Vampire", "V") {}
};

class VampireKing : public Enemy {   // Cave BOSS | Avg HP: 155 | Avg DMG: 13
    public:
        VampireKing() : Enemy(rollDie(20, 10) + 50, rollDie(8, 2) + 4, 0, 7000, "Vampire King", "\033[33mK\033[0m") {
            setAggro(true);
        }
};

#endif
