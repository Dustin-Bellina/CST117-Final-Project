#ifndef DEFS_H
#define DEFS_H

#define elif else if

// Debug Flags
#define DEBUG_MAP false
#define DEBUG_KEYS false
#define DEBUG_ENEMIES false
#define GODMODE false

// Screen/Map Dimensions
#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80
#define MAP_HEIGHT 20
#define MAP_WIDTH 77
#define MAX_ROOM_HEIGHT 6
#define MAX_ROOM_WIDTH 25

// Limits per Room
#define MAX_ENEMIES 3
#define MAX_ITEMS 5

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

// Letter Keys
#define KEY_a 97
#define KEY_b 98
#define KEY_c 99
#define KEY_d 100   // DEBUG
#define KEY_e 101
#define KEY_g 103   // DEBUG
#define KEY_i 105
#define KEY_s 115
#define KEY_y 121

// Special Keys
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_FORWARD_SLASH 47
#define KEY_SPACE 32
#define KEY_PgUp 73
#define KEY_PgDn 81
#define KEY_HOME 71
#define KEY_END 79

// Map Symbols
#define TL_WALL "╔"
#define BL_WALL "╚"
#define TR_WALL "╗"
#define BR_WALL "╝"
#define SIDE_WALL "║"
#define TB_WALL "═"
#define DOOR "╬"
#define HALL "▒"
#define FLOOR "."
#define PLAYER "@"
#define SHOP "⌂"
#define ENTERANCE "☼"

// Item Symbols
#define GOLD "☉"
#define SIGN "↑"
#define BREAD "♣"
#define POTION "♪"

// ANSI Escape Codes
#define CURSOR_HOME "\033[H"
#define CLEAR_LINE "\033[2K"
#define FG_BLACK "\033[30m"
#define FG_GREY "\033[90m"
#define FG_RED "\033[31m"
#define BG_GREY "\033[100m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_WHITE "\033[47m"
#define RESET_STYLE "\033[0m"

// Player Stat Calculations
#define STRENGTH_MODIFIER(s) ((int)floor(((s) - 10) / 2.0))
#define PLAYER_DAMAGE (rollDie(8, player.level) + 1 + STRENGTH_MODIFIER(player.strength))

// Item List
inline const std::string ITEM_LIST[] = {
    BREAD,
    GOLD,
    POTION
};

#endif
