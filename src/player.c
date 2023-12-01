#include "player.h"
#include "orc.h"
#include "setup.h"

extern Player player;

// void draw_player(const Player *player) { mvprintw(player->y, player->x, "@");
// }

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

void place_player_in_new_level(Map *map) {
  place_player(map);
  player.old_x = player.x;
  player.old_y = player.y;
}

void player_setup(Map *map) {
  player.x = PLAYER_START_X;
  player.y = PLAYER_START_Y;
  player.old_x = player.x;
  player.old_y = player.y;
  player.max_health = 50;
  player.max_armour = 50;
  player.health = player.max_health;
  player.armour = 0;
  player.damage = 10;
  player.has_sword = false;
  place_player(map);
}

void move_player(int ch, Player *player, Map *map) {
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
  }

  player->move_counter++;

  // Check for collision at the new position
  if (!check_collision(map, new_y, new_x)) {
    // Update player position if no collision
    player->y = new_y;
    player->x = new_x;
  }
}

void draw_status_bar(int y, int x, int current, int max, int color_pair,
                     char symbol) {
  int width = 25; // Max width of the status bar
  int filled = (int)(((float)current / (float)max) * width);

  move(y, x);
  clrtoeol();

  attron(COLOR_PAIR(color_pair));
  for (int i = 0; i < filled; i++) {
    mvprintw(y, x + i, "%c", symbol);
  }
  attroff(COLOR_PAIR(color_pair));
}

// Draw both the status bars (1 cell = 2 health/armour points)
void draw_player_status(const Player *player) {
  mvprintw(MAP_HEIGHT, 0, "> ");

  int status_bar_y = MAP_HEIGHT + 1;

  draw_status_bar(status_bar_y, 0, player->health / 2, player->max_health / 2,
                  COLOR_PAIR_HEALTH, 'H');

  draw_status_bar(status_bar_y + 1, 0, player->armour / 2,
                  player->max_armour / 2, COLOR_PAIR_ARMOUR, 'A');

  mvprintw(status_bar_y + 2, 0, "Health: %d", player->health);
  mvprintw(status_bar_y + 3, 0, "Armour: %d", player->armour);
  mvprintw(status_bar_y + 4, 0, "Damage: %d", player->damage);
}

// This optimizes the screen refresh by only redrawing where the player was
// standing, and where they are now.
// This function would make more sense in the map file, but that won't work
// properly based on the way I'm importing my files :/
void optimized_redraw(Player *player, char *tile_under_player, Map *map) {
  // Redraw the tile or orc that was under the player
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
  attron(COLOR_PAIR(COLOR_PAIR_BLUE));
  mvprintw(player->y, player->x, "@");
  attroff(COLOR_PAIR(COLOR_PAIR_BLUE));
}
