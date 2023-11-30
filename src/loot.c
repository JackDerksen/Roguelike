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
      mvprintw(MAP_HEIGHT, 2, "You picked up a sword! Damage +20");
      player->damage += 20;
      player->has_sword = true;
      break;
    } else {
      mvprintw(MAP_HEIGHT, 2, "You upgraded your sword! Damage +10");
      player->damage += 10;
      break;
    }
  case LOOT_HEALTH:
    if (player->health <= 25) {
      mvprintw(MAP_HEIGHT, 2, "You picked up some health! Health +25");
      player->health += 25;
    } else {
      int h_incr = player->max_health - player->health;
      mvprintw(MAP_HEIGHT, 2, "You picked up some health! Health +%d", h_incr);
      player->health = player->max_health;
    }
    break;
  case LOOT_ARMOUR:
    if (player->armour <= 25) {
      mvprintw(MAP_HEIGHT, 2, "You picked up some armour! Armour +25");
      player->armour += 25;
    } else {
      int a_incr = player->max_armour - player->armour;
      mvprintw(MAP_HEIGHT, 2, "You picked up some armour! Armour +%d", a_incr);

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
