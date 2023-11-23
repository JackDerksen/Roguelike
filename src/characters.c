#include "characters.h"

// This module should contain all of the functions and data structures related
// to each character (player, enemies, npcs, etc.) and their statistics,
// inventory management, and other character-specific logic.

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
  player.old_x = player.x;
  player.old_y = player.y;
  player.health = CHARACTER_MAX_HEALTH;
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

  // Check for collision at the new position
  if (!check_collision(map, new_y, new_x)) {
    // Update player position if no collision
    player->y = new_y;
    player->x = new_x;
  }
}

// This optimizes the screen refresh by only redrawing where the player was
// standing, and where they are now.
void optimized_redraw(Character *player, char *tile_under_player, Map *map) {
  char old_tile_char = (*tile_under_player == 'C') ? 'C' : '.';
  if (old_tile_char == 'C') {
    attron(COLOR_PAIR(COLOR_PAIR_CHEST));
  } else {
    attron(COLOR_PAIR(COLOR_PAIR_FLOORS));
  }
  mvprintw(player->old_y, player->old_x, "%c", old_tile_char);
  attroff(COLOR_PAIR(COLOR_PAIR_CHEST));
  attroff(COLOR_PAIR(COLOR_PAIR_FLOORS));

  // Update tile_under_player
  *tile_under_player = map->tiles[player->y][player->x];

  // Draw the player at the new position
  attron(COLOR_PAIR(3));
  mvprintw(player->y, player->x, "@");
  attroff(COLOR_PAIR(3));
}
