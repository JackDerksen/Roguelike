#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include "setup.h"
#include <ncurses.h>
#include <stdbool.h>

/**
 * @brief Pauses the game until the player presses 'p'.
 */
void pause_game(void);

/**
 * @brief Confirms with the player before quitting the game.
 * @return True if the player confirms to quit, otherwise false.
 */
bool confirm_quit(void);

#endif // GAME_CONTROL_H
