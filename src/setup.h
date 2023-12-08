#ifndef SETUP_H
#define SETUP_H

#include <ncurses.h>

#define COLOR_PAIR_BLUE 1
#define COLOR_PAIR_WALLS 2
#define COLOR_PAIR_FLOORS 3
#define COLOR_PAIR_EXIT 4
#define COLOR_PAIR_CHEST 5
#define COLOR_PAIR_GAME_TEXT 6
#define COLOR_PAIR_HEALTH 7
#define COLOR_PAIR_ARMOUR 8
#define COLOR_PAIR_ORC 9

/**
 * @brief Sets up the initial screen for the game.
 * @return Returns 0 on successful setup.
 */
int screen_setup(void);

#endif // SETUP_H
