#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

// Alir Louis
struct playerType {
    int health;
    int maxHealth;

    int strength;
    int armorClass;

    int healthPotions;
    int strengthPotions;
    int bread;

    int gold;

    int level;

    std::string stage;
    int sublevel;
    int x, y;
    int xp;
};

// Dustin Bellina
struct roomType {
    int x1, y1, x2, y2;
};

#endif
