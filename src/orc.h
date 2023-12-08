#ifndef ORC_H
#define ORC_H

#include "collisions.h"
#include "map.h"
#include "player.h"
#include "splash.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ORCS 8

/**
 * @brief Structure representing an orc in the game.
 * Contains all necessary information about an orc, such as its position,
 * health, damage, movement counter, and alive status.
 */
typedef struct {
  int x, y;         ///< Current x and y coordinates of the orc.
  int old_x, old_y; ///< Previous x and y coordinates of the orc.
  int health;       ///< Current health of the orc.
  int max_health;   ///< Maximum health of the orc.
  int damage;       ///< Damage dealt by the orc.
  int move_counter; ///< Counter to track orc movement.
  bool is_alive;    ///< Flag indicating whether the orc is alive.
} Orc;

extern Orc orcs[];   ///< Array of all orcs in the game.
extern int num_orcs; ///< Number of orcs currently in the game.

/**
 * @brief Initializes the orcs in the game.
 */
void initialize_orcs(void);

/**
 * @brief Places orcs on the game map.
 * @param map Pointer to the Map structure where orcs will be placed.
 */
void place_orcs(Map *map);

/**
 * @brief Checks if a space is occupied by an orc, excluding a specified orc.
 * @param x X-coordinate of the space to check.
 * @param y Y-coordinate of the space to check.
 * @param excluding_orc_index Index of the orc to exclude from the check.
 * @return True if the space is occupied by another orc, false otherwise.
 */
bool is_space_occupied_by_orc(int x, int y, int excluding_orc_index);

/**
 * @brief Checks if a space is occupied by the player.
 * @param x X-coordinate of the space to check.
 * @param y Y-coordinate of the space to check.
 * @param player Pointer to the Player structure to compare the position with.
 * @return True if the space is occupied by the player, false otherwise.
 */
bool is_space_occupied_by_player(int x, int y, Player *player);

/**
 * @brief Determines if a player is adjacent to an orc.
 * @param player Pointer to the Player structure.
 * @param orc Pointer to the Orc structure.
 * @return True if the player is adjacent to the orc, false otherwise.
 */
bool is_adjacent(Player *player, Orc *orc);

/**
 * @brief Calculates the Manhattan distance between two points.
 * @param x1 X-coordinate of the first point.
 * @param y1 Y-coordinate of the first point.
 * @param x2 X-coordinate of the second point.
 * @param y2 Y-coordinate of the second point.
 * @return The Manhattan distance between the two points.
 */
int manhattan_distance(int x1, int y1, int x2, int y2);

/**
 * @brief Moves orcs towards the player based on certain conditions.
 * @param player Pointer to the Player structure representing the game's player.
 * @param map Pointer to the Map structure representing the game world.
 * @param frame_counter The current frame number in the game loop, used for
 * movement timing.
 */
void move_orcs_towards_player(Player *player, Map *map, int frame_counter);

#endif // ORC_H
