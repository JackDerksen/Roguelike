#include "attacking.h"
#include "map.h"

/**
 * @brief Attacks an orc if the player is adjacent to it.
 *
 * This function calculates the damage dealt by the player to the orc.
 * If the orc's health falls below zero, it marks the orc as not alive.
 * It also updates the game dialogue with the result of the attack.
 *
 * @param player Pointer to the player's data structure.
 * @param orc Pointer to the orc's data structure.
 */
void player_attack_orc(Player *player, Orc *orc) {
  if (is_adjacent(player, orc)) {
    int damageDealt = player->damage;
    orc->health -= damageDealt;

    if (orc->health <= 0) {
      orc->is_alive = false;
      clear_dialogue();
      mvprintw(MAP_HEIGHT, 2, "Orc defeated! ");
    } else {
      // Display damage feedback
      clear_dialogue();
      mvprintw(MAP_HEIGHT, 2, "You hit the orc! Damage: %d, Orc health: %d ",
               damageDealt, orc->health);
    }
  }
}

// orc_attack_player defined in orc.c

/**
 * @brief Checks if the player is adjacent to an orc.
 *
 * This function determines if the player's position is within one unit of the
 * orc's position on the map.
 *
 * @param player Pointer to the player's data structure.
 * @param orc Pointer to the orc's data structure.
 * @return True if the player is adjacent to the orc, otherwise false.
 */
bool is_adjacent(Player *player, Orc *orc) {
  return abs(player->x - orc->x) <= 1 && abs(player->y - orc->y) <= 1;
}
