#ifndef SETUP_H
#define SETUP_H

#include <ncurses.h>

#define COLOR_PAIR_RED 1
#define COLOR_PAIR_GREEN 2
#define COLOR_PAIR_BLUE 3
#define COLOR_PAIR_WALLS 4
#define COLOR_PAIR_FLOORS 5
#define COLOR_PAIR_EXIT 6
#define COLOR_PAIR_CHEST 7
#define COLOR_PAIR_GAME_TEXT 8

int screen_setup(void);

#endif // SETUP_H
