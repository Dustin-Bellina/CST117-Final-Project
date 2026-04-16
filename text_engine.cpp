/*
Functions:
    te_print(): Text Engine Print: Prints text to the top of the screen
    te_error(): Text Engine Error: Prints an error message to the top of the screen
	more(): Handles text when there is too much text on screen
    wait(): Waits for the player to press any key
*/

#include <iostream>
#include <conio.h>
#include <string>

#include "defs.h"
#include "prototypes.h"


using namespace std;


void te_print(string message) {
    cout << CURSOR_HOME << CLEAR_LINE << message << flush;
}

void te_error(string message) {
    cout << CURSOR_HOME << CLEAR_LINE << FG_RED << message << RESET_STYLE << flush;
}

void more() {
    int choice = 0;
    cout << MORE << RESET_STYLE;
    while ((choice = _getch()) != KEY_SPACE) { /*THIS SPACE INTENTIONALLY LEFT EMPTY*/ }
}

// A bit of a poor-man's way of waiting for the player to press anything
void wait() {
    int ch = 0;
    ch = _getch();

    if (ch == 0 || ch == 224) { ch = _getch(); }    // Handle special keys if pressed
}
