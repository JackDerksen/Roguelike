#include "loot.h"
#include "characters.h"
#include "map.h"
#include <curses.h>

// This file will contain a list of all the possible loot (armour, weapons,
// potions, etc.), and some logic for looting chests. Maybe also for getting
// gold from enemies, although that might be better suited to the characters
// file (?).

void handle_loot(Character *player, LootType loot) {
  switch (loot) {
  case LOOT_SWORD:
    mvprintw(MAP_HEIGHT + 1, 27, "Picked up a sword!");
    player->damage += 5;
    break;
  case LOOT_HEALTH:
    mvprintw(MAP_HEIGHT + 1, 27, "Picked up extra health!");
    if (player->health <= 25) {
      player->health += 25;
    } else {
      player->health = player->max_health;
    }
    break;
  case LOOT_ARMOUR:
    mvprintw(MAP_HEIGHT + 1, 27, "Picked up extra armour!");
    if (player->armour <= 25) {
      player->armour += 25;
    } else {
      player->armour = player->max_armour;
    }
    break;
  default:
    // Handle unknown loot type
    break;
  }

  player->move_counter = 0;

  refresh();
}

LootType generate_random_loot() { return rand() % LOOT_MAX_TYPE; }
