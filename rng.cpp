/*
Contains functions relating to the game's RNG

Functions:
rollDie() : Simulate rolling a die of specified sides a specified amount of times
*/

#include <iostream>
#include <random>

using namespace std;


int rollDie(int sides, int rolls) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(1, sides);

    int sum = 0;

    for (int i = 0; i < rolls; i++) {
        sum += distr(gen);
    }

    return sum;
}
