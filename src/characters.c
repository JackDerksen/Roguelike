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
  character->x = CHARACTER_START_X;
  character->y = CHARACTER_START_Y;
  character->health = CHARACTER_MAX_HEALTH;
  // Other initializations
}

void draw_character(const Character *character) {
  mvprintw(character->y, character->x, "@");
}

void place_player(Map *map) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if (map->tiles[y][x] == '.') {
        player.x = x;
        player.y = y;
        return; // Exit the function once a valid spot is found
      }
    }
  }
}

void player_setup(Map *map) {
  player.x = CHARACTER_START_X;
  player.y = CHARACTER_START_Y;
  player.health = CHARACTER_MAX_HEALTH;
  place_player(map);
}
