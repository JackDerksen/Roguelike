#include "player.h"
#include "setup.h"

extern Player player;

/**
 * @brief Places the player on a valid starting position on the map.
 *
 * Iterates through the map tiles to find the first available floor ('.') tile
 * and places the player there.
 *
 * @param map Pointer to the Map structure where the player will be placed.
 */
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

/**
 * @brief Places the player in a new level.
 *
 * Calls place_player to find a new starting position for the player when a new
 * level of the game is started.
 *
 * @param map Pointer to the Map structure representing the new level.
 */
void place_player_in_new_level(Map *map) {
  place_player(map);
  player.old_x = player.x;
  player.old_y = player.y;
}

/**
 * @brief Initializes the player's properties.
 *
 * Sets up the player's starting position, health, armour, damage, and other
 * attributes at the beginning of the game.
 *
 * @param map Pointer to the Map structure where the player will be initialized.
 */
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

/**
 * @brief Moves the player based on input character.
 *
 * Updates the player's position depending on the input character (e.g., arrow
 * keys). It also handles the logic for what happens when the player moves
 * (e.g., encountering an obstacle).
 *
 * @param ch The input character indicating the direction of movement.
 * @param player Pointer to the Player structure representing the game's player.
 * @param map Pointer to the Map structure representing the game world.
 */
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

/**
 * @brief Draws a status bar (e.g., health, armour) on the game screen.
 *
 * Renders a status bar at a specified location with the given attributes.
 *
 * @param y Y-coordinate for the status bar.
 * @param x X-coordinate for the status bar.
 * @param current The current value to be displayed in the status bar.
 * @param max The maximum value of the status bar.
 * @param color_pair Color pair for NCurses display.
 * @param symbol Character symbol used to represent the status bar.
 */
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

/**
 * @brief Draws the player's current status on the screen.
 *
 * Displays the player's health, armour, and other status information on the
 * game screen.
 *
 * @param player Pointer to the constant Player structure representing the
 * game's player.
 */
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

/**
 * @brief Optimizes and redraws the player and the tile they are on.
 *
 * This function is used to efficiently redraw the player's character and the
 * tile they are standing on, to reflect any changes in the game state.
 *
 * @param player Pointer to the Player structure representing the game's player.
 * @param tile_under_player Character representing the tile under the player.
 * @param map Pointer to the Map structure representing the game world.
 */
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
