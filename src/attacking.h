// attacking.h

#ifndef ATTACKING_H
#define ATTACKING_H

#include "map.h"
#include "orc.h"
#include "player.h"
#include <ncurses.h>

/**
 * @brief Allows the player to attack an orc.
 * @param player Pointer to the Player structure representing the game's player.
 * @param orc Pointer to the Orc structure representing the target of the
 * attack.
 */
void player_attack_orc(Player *player, Orc *orc);

/**
 * @brief Checks if a player is adjacent to an orc.
 * @param player Pointer to the Player structure.
 * @param orc Pointer to the Orc structure.
 * @return True if the player is adjacent to the orc, false otherwise.
 */
bool is_adjacent(Player *player, Orc *orc);

#endif // ATTACKING_H
