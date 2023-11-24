#include "characters.h"
#include "map.h"

// This module should contain all of the functions and data structures related
// to each character (player, enemies, npcs, etc.) and their statistics,
// inventory management, and other character-specific logic.

extern Character player;
extern Character orc;

// Will be used again for other character instances (enemies, npcs, etc.)
void initialize_character(Character *character) {
  character->x = CHARACTER_START_X;
  character->y = CHARACTER_START_Y;
  character->health = character->max_health;
  character->armour = character->max_armour;
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
  player.old_x = player.x;
  player.old_y = player.y;
  player.max_health = 50;
  player.max_armour = 50;
  player.health = player.max_health;
  player.armour = player.max_armour;
  place_player(map);
}

void move_player(int ch, Character *player, Map *map) {
  // Storing the old position
  player->old_x = player->x;
  player->old_y = player->y;

  int new_y = player->y;
  int new_x = player->x;

  // Determine new position based on input
  switch (ch) {
  case KEY_UP:
  case 'k': // Vim keybinding for up
    new_y--;
    break;
  case KEY_DOWN:
  case 'j': // Vim keybinding for down
    new_y++;
    break;
  case KEY_LEFT:
  case 'h': // Vim keybinding for left
    new_x--;
    break;
  case KEY_RIGHT:
  case 'l': // Vim keybinding for right
    new_x++;
    break;
    // Add more cases if there are more controls down the line
  }

  player->move_counter++;

  // Check for collision at the new position
  if (!check_collision(map, new_y, new_x)) {
    // Update player position if no collision
    player->y = new_y;
    player->x = new_x;
  }
}

void draw_status_bar(int y, int x, int current, int max, int color_pair) {
  int width = 25; // Max width of the status bar
  int filled = (int)(((float)current / (float)max) * width);

  attron(COLOR_PAIR(color_pair));
  for (int i = 0; i < filled; i++) {
    mvprintw(y, x + i, " ");
  }
  attroff(COLOR_PAIR(color_pair));
}

// Draw both the status bars (1 cell = 2 health/armour points)
void draw_character_status(const Character *player) {
  int status_bar_y = MAP_HEIGHT + 1;

  draw_status_bar(status_bar_y, 0, player->health / 2, player->max_health / 2,
                  COLOR_PAIR_HEALTH);

  draw_status_bar(status_bar_y + 1, 0, player->armour / 2,
                  player->max_armour / 2, COLOR_PAIR_ARMOUR);
}

// This optimizes the screen refresh by only redrawing where the player was
// standing, and where they are now.
// This function would make more sense in the map file, but that won't work
// properly based on the way I'm importing my files :/
void optimized_redraw(Character *player, char *tile_under_player, Map *map) {
  // Redraw the tile that was under the player
  if (*tile_under_player == 'C') {
    attron(COLOR_PAIR(COLOR_PAIR_CHEST));
  } else {
    attron(COLOR_PAIR(COLOR_PAIR_FLOORS));
  }
  mvprintw(player->old_y, player->old_x, "%c", *tile_under_player);
  attroff(COLOR_PAIR(COLOR_PAIR_CHEST));
  attroff(COLOR_PAIR(COLOR_PAIR_FLOORS));

  // Update tile_under_player to the new tile
  *tile_under_player = map->tiles[player->y][player->x];

  // If the player stepped on a chest, change it to a floor tile
  if (*tile_under_player == 'C') {
    *tile_under_player = '.';
    map->tiles[player->y][player->x] = '.';
  }

  // Draw the player at the new position
  attron(COLOR_PAIR(3));
  mvprintw(player->y, player->x, "@");
  attroff(COLOR_PAIR(3));
}
