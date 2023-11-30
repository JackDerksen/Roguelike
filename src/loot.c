#include "loot.h"
#include "map.h"
#include "player.h"
#include <curses.h>

// This file will contain a list of all the possible loot (armour, weapons,
// potions, etc.), and some logic for looting chests. Maybe also for getting
// gold from enemies, although that might be better suited to the player
// file (?).

void handle_loot(Player *player, LootType loot) {
  switch (loot) {
  case LOOT_SWORD:
    if (!player->has_sword) {
      mvprintw(MAP_HEIGHT, 2, "Picked up a sword!");
      player->damage += 20;
      player->has_sword = true;
      break;
    } else {
      mvprintw(MAP_HEIGHT, 2, "You upgraded your sword!");
      player->damage += 10;
      break;
    }
  case LOOT_HEALTH:
    mvprintw(MAP_HEIGHT, 2, "Picked up extra health!");
    if (player->health <= 25) {
      player->health += 25;
    } else {
      player->health = player->max_health;
    }
    break;
  case LOOT_ARMOUR:
    mvprintw(MAP_HEIGHT, 2, "Picked up extra armour!");
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
