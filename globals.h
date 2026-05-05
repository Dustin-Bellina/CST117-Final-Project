#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>

// Enemy List
inline const std::string ENEMY_LIST[] = {
    "A","B","C","D","E","F","G","H","I","J","K","L","M",
    "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
};
inline const std::string BOSS_LIST[] = {
    "\033[36mO\033[0m", "\033[31mD\033[0m", "\033[32mT\033[0m", "\033[33mK\033[0m"
};

// Hit/Miss Messages
inline const std::string ENEMY_HIT_MESSAGES[] = { " hits you", " strikes you", " injures you", "'s attack hits you hard" };
inline const std::string ENEMY_MISS_MESSAGES[] = { " misses you", " barely misses you", " swings and misses you" };
inline const std::string PLAYER_HIT_MESSAGES[] = { "You hit the ", "You strike the ", "You injure the ", "You swing and hit the " };
inline const std::string PLAYER_MISS_MESSAGES[] = { "You miss the ", "You barely miss the ", "You swing and miss the " };

// Kill Messages
inline const std::string KILL_MESSAGES[] = {
    "You have slain the ",
    "You have killed the ",
    "You slayed the ",
    "You killed the "
};

// Message Queue
inline std::vector<std::string> MESSAGE_QUEUE;

// Turn Counter
inline int TURN = 0;

#endif