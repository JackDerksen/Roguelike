#ifndef LOOT_H
#define LOOT_H

#include "player.h"
#include <stdlib.h>

/**
 * @brief Enum for different types of loot.
 */
typedef enum {
  LOOT_SWORD,   ///< Represents a sword loot item
  LOOT_HEALTH,  ///< Represents a health bonus loot item
  LOOT_ARMOUR,  ///< Represents an armour bonus loot item
  LOOT_MAX_TYPE ///< Used in the loot generation algorithm
} LootType;

/**
 * @brief Handles the player's interaction with loot.
 * @param player Pointer to the Player structure.
 * @param loot The type of loot interacted with.
 */
void handle_loot(Player *player, LootType loot);

/**
 * @brief Generates a random type of loot.
 * @return A random LootType value.
 */
LootType generate_random_loot();

#endif // LOOT_H
