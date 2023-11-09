#include "characters.h"

// This module should contain all of the functions and data structures related
// to each character (player, enemies, npcs, etc.) and their statistics,
// inventory management, and other character-specific logic.
//
// In player.h, declare the structure representing the player and any public
// functions. In player.c, define these functions. The player_setup() function
// in characters.c would call an initialization function from this module to set
// up the player.

extern Character player;

// Will be used again for other character instances (enemies, npcs, etc.)
void initialize_character(Character *character) {
  character->x = START_X;
  character->y = START_Y;
  character->health = MAX_HEALTH;
  // Other initializations
}

void draw_character(const Character *character) {
  mvprintw(character->y, character->x, "@");
}

void player_setup(void) {
  player.x = START_X;
  player.y = START_Y;
  player.health = MAX_HEALTH;
}
