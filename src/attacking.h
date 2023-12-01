// attacking.h

#ifndef ATTACKING_H
#define ATTACKING_H

#include "map.h"
#include "orc.h"
#include "player.h"
#include <ncurses.h>

void player_attack_orc(Player *player, Orc *orc);
bool is_adjacent(Player *player, Orc *orc);

#endif // ATTACKING_H
