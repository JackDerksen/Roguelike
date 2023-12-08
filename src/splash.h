#ifndef SPLASH_H
#define SPLASH_H

#include <ncurses.h>

/**
 * @brief Displays the title splash screen for the game, with some brief
 * instructions on how to play.
 */
void show_splash_screen(void);

/**
 * @brief Displays the game over splash screen.
 */
void game_over_screen(void);

#endif // SPLASH_H
