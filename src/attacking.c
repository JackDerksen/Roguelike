#include "attacking.h"

void player_attack_orc(Player *player, Orc *orc) {
  if (is_adjacent(player, orc)) {
    int damageDealt = player->damage;
    orc->health -= damageDealt;

    if (orc->health <= 0) {
      orc->is_alive = false;
      mvprintw(MAP_HEIGHT, 2, "Orc defeated! ");
    } else {
      // Display damage feedback
      mvprintw(MAP_HEIGHT, 2, "You hit the orc! Damage: %d, Orc health: %d ",
               damageDealt, orc->health);
    }
  }
}

// orc_attack_player defined in orc.c

bool is_adjacent(Player *player, Orc *orc) {
  return abs(player->x - orc->x) <= 1 && abs(player->y - orc->y) <= 1;
}
