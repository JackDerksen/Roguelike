#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include "setup.h"
#include <ncurses.h>
#include <stdbool.h>

void pause_game(void);
bool confirm_quit(void);

#endif // GAME_CONTROL_H
