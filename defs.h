#ifndef DEFS_H
#define DEFS_H

// Convenience
#define elif else if

#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_FORWARD_SLASH 47
#define KEY_SPACE 32

// Arrow Keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// Number Keys
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

// Lowercase Letter Keys
#define KEY_a 97
#define KEY_b 98
#define KEY_c 99
#define KEY_d 100
#define KEY_e 101
#define KEY_f 102
#define KEY_g 103
#define KEY_h 104
#define KEY_i 105
#define KEY_j 106
#define KEY_k 107
#define KEY_l 108
#define KEY_m 109
#define KEY_n 110
#define KEY_o 111
#define KEY_p 112
#define KEY_q 113
#define KEY_r 114
#define KEY_s 115
#define KEY_t 116
#define KEY_u 117
#define KEY_v 118
#define KEY_w 119
#define KEY_x 120
#define KEY_y 121
#define KEY_z 122

// Screen Dimensions
#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

// Map Dimensions
#define MAP_HEIGHT 20
#define MAP_WIDTH 77
#define MAX_ROOM_HEIGHT 6
#define MAX_ROOM_WIDTH 25

// Walls
#define TL_WALL "╔"
#define BL_WALL "╚"
#define TR_WALL "╗"
#define BR_WALL "╝"
#define SIDE_WALL "║"
#define TB_WALL "═"
#define DOOR "╬"
#define HALL "▒"
#define FLOOR "."

// Character Codes
#define PLAYER "@"
#define SIGN "↑"
#define SHOP "⌂"
#define SEWER_ENTERANCE "☼"

// ANSI Escape Codes for Text
#define CURSOR_HOME "\033[H"
#define CLEAR_LINE "\033[2K"
#define RESET_STYLE "\033[0m"
#define MORE "\033[47;30m MORE "

#define FG_GREY "\033[90m"
#define FG_RED "\033[41m"

#define BG_GREY "\033[100m"

#endif
