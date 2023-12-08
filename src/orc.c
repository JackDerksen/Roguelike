#include "orc.h"
#include "map.h"
#include "splash.h"

extern Player player;

Orc orcs[MAX_ORCS];
int num_orcs;

/**
 * @brief Initializes the orcs in the game.
 *
 * Sets the initial properties for each orc, including position, health, damage,
 * and alive status. The number of orcs is randomized within a specific range.
 */
void initialize_orcs(void) {
  num_orcs = (rand() % 5) + 4; // Random number between 4 and 8

  for (int i = 0; i < num_orcs; i++) {
    orcs[i].x = -1;
    orcs[i].y = -1;
    orcs[i].health = 40;
    orcs[i].max_health = 100;
    orcs[i].damage = 10;
    orcs[i].is_alive = true;
  }
}

/**
 * @brief Randomly places orcs on the game map.
 *
 * Places each orc on a random location within the map, ensuring they are placed
 * on a floor tile ('.') and not on the player's position. This function is
 * called once when initializing the game state.
 *
 * @param map Pointer to the Map structure where orcs will be placed.
 */
void place_orcs(Map *map) {
  for (int i = 0; i < num_orcs; i++) {
    int x, y;
    do {
      x = rand() % MAP_WIDTH;
      y = rand() % MAP_HEIGHT;
    } while (map->tiles[y][x] != '.' || (x == player.x && y == player.y));

    orcs[i].x = x;
    orcs[i].y = y;
  }
}

/**
 * @brief Calculates the Manhattan distance between two points.
 *
 * The Manhattan distance is the sum of the absolute differences of their
 * Cartesian coordinates. This function is used to determine the distance
 * between two entities in the game.
 *
 * @param x1 X-coordinate of the first point.
 * @param y1 Y-coordinate of the first point.
 * @param x2 X-coordinate of the second point.
 * @param y2 Y-coordinate of the second point.
 * @return The Manhattan distance between the two points.
 */
int manhattan_distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

/**
 * @brief Checks if a map space is occupied by an orc, excluding a specific orc.
 *
 * This function is used to determine if a given space on the map is already
 * occupied by an orc, which is useful when moving or placing orcs.
 *
 * @param y Y-coordinate of the space to check.
 * @param x X-coordinate of the space to check.
 * @param excluding_orc_index Index of the orc to exclude from the check.
 * @return True if the space is occupied by another orc, false otherwise.
 */
bool is_space_occupied_by_orc(int y, int x, int excluding_orc_index) {
  for (int i = 0; i < num_orcs; i++) {
    if (i != excluding_orc_index && orcs[i].x == x && orcs[i].y == y) {
      return true; // Another orc is already at this position
    }
  }
  return false;
}

/**
 * @brief Checks if a map space is occupied by the player.
 *
 * Determines whether the specified coordinates on the map are the current
 * position of the player.
 *
 * @param y Y-coordinate of the space to check.
 * @param x X-coordinate of the space to check.
 * @param player Pointer to the Player structure to compare the position with.
 * @return True if the space is occupied by the player, false otherwise.
 */
bool is_space_occupied_by_player(int y, int x, Player *player) {
  return player->x == x && player->y == y;
}

/**
 * @brief Determines if the player is adjacent to an orc.
 *
 * Checks whether the player is within one tile (in any direction) from the orc.
 * Used to determine if the orc can attack the player.
 *
 * @param player Pointer to the Player structure.
 * @param orc Pointer to the Orc structure.
 * @return True if the player is adjacent to the orc, false otherwise.
 */
bool is_adjacent(Player *player, Orc *orc) {
  return abs(player->x - orc->x) <= 1 && abs(player->y - orc->y) <= 1;
}

/**
 * @brief Moves orcs towards the player based on certain conditions.
 *
 * Each orc moves towards the player if within a certain distance threshold. If
 * an orc is adjacent to the player, it attacks instead of moving. This function
 * is called every game frame to update orc positions.
 *
 * @param player Pointer to the Player structure representing the game's player.
 * @param map Pointer to the Map structure representing the game world.
 * @param frame_counter The current frame number in the game loop, used for
 * movement timing.
 */
void move_orcs_towards_player(Player *player, Map *map, int frame_counter) {
  const int ORC_MOVEMENT_THRESHOLD = 10;
  bool is_move_frame = (frame_counter % 2 == 0);

  for (int i = 0; i < num_orcs; i++) {
    // Skip the dead orcs
    if (!orcs[i].is_alive) {
      continue;
    }

    if (is_move_frame &&
        manhattan_distance(player->x, player->y, orcs[i].x, orcs[i].y) <=
            ORC_MOVEMENT_THRESHOLD) {
      if (is_adjacent(player, &orcs[i])) {
        // Orc attacks the player
        int damageDealt = orcs[i].damage;
        player->health -= damageDealt;

        if (player->health <= 0) {
          // Handle player defeat
          game_over_screen();
          int ch = getch();
          if (ch) {
            endwin(); // Close the ncurses window
            exit(0);  // Terminate the program
          }
        } else {
          // Display damage feedback
          clear_dialogue();
          mvprintw(MAP_HEIGHT, 2, "Orc hits you! Damage: %d, Your health: %d ",
                   damageDealt, player->health);
        }
      } else {
        // Determine the direction of movement
        int dx = (player->x > orcs[i].x) ? 1 : (player->x < orcs[i].x) ? -1 : 0;
        int dy = (player->y > orcs[i].y) ? 1 : (player->y < orcs[i].y) ? -1 : 0;

        // Calculate potential new position
        int new_x = orcs[i].x + dx;
        int new_y = orcs[i].y + dy;

        // Check if the new position is occupied by the player or is a collision
        if (!is_space_occupied_by_player(new_x, new_y, player) &&
            !check_collision(map, new_y, new_x) &&
            !is_space_occupied_by_orc(new_y, new_x, i)) {
          // Update orc's position
          orcs[i].x = new_x;
          orcs[i].y = new_y;
        }
      }
    }
  }
}
