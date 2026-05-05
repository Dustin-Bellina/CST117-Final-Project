/*
Contains functions to show and hide the cursor
*/

#include <iostream>

using namespace std;


void hideCursor() {
	cout << "\033[?25l";
}

void showCursor() {
	cout << "\033[?25h";
}