#ifndef LOOT_H
#define LOOT_H

#include "player.h"
#include <stdlib.h>

typedef enum {
  LOOT_SWORD,
  LOOT_HEALTH,
  LOOT_ARMOUR,
  LOOT_MAX_TYPE // This is used for generating random loot
} LootType;

void handle_loot(Player *player, LootType loot);
LootType generate_random_loot();

#endif // LOOT_H
