/*
Dustin Bellina

Contains the text engine for the game

Functions:
more() : cout MORE when necessary
wait() : Wait until the player presses any button
te_print() : Print a message to the top of the screen
te_error() : Print an error message to the top of the screen
te_success() : Print a success message to the top of the screen
message() : Load a message to the queue to be printed later
flushMessages() : Iterate through the message queue
*/

#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include "defs.h"
#include "globals.h"
// Functions are arranged in a way to avoid having to include prototypes.h

using namespace std;


void more() {
    cout << BG_WHITE << FG_BLACK << " MORE " << RESET_STYLE << flush;
}

void wait() {
    while (_getch() != KEY_SPACE) {}
}

void te_print(string message) {
    cout << CURSOR_HOME << CLEAR_LINE << message << flush;
}

void te_error(string message) {
    cout << CURSOR_HOME << CLEAR_LINE << BG_RED << message << RESET_STYLE << flush;
}

void te_success(string message) {
    cout << CURSOR_HOME << CLEAR_LINE << BG_GREEN << message << RESET_STYLE << flush;
}

void message(string msg) {
    MESSAGE_QUEUE.push_back(msg);
}

void flushMessages() {
    for (int i = 0; i < (int)MESSAGE_QUEUE.size(); i++) {
        te_print(MESSAGE_QUEUE[i]);

        if (i < (int)MESSAGE_QUEUE.size() - 1) {
            more();
            wait();
        }
    }
    MESSAGE_QUEUE.clear();
}
