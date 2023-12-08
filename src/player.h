#ifndef PLAYER_H
#define PLAYER_H

#include "collisions.h"
#include "map.h"
#include <ncurses.h>

#define PLAYER_START_X 10
#define PLAYER_START_Y 10

/**
 * @brief Structure representing the player in the game.
 */
typedef struct {
  int x, y;         ///< Current x and y coordinates of the player.
  int old_x, old_y; ///< Previous x and y coordinates of the player.
  int health;       ///< Current health of the player.
  int max_health;   ///< Maximum health of the player.
  int armour;       ///< Current armour of the player.
  int max_armour;   ///< Maximum armour of the player.
  int damage;       ///< Damage dealt by the player.
  int move_counter; ///< Counter to track player movement.
  bool has_sword;   ///< Flag indicating whether the player has a sword.
} Player;

/**
 * @brief Places the player on a valid starting position on the map.
 * @param map Pointer to the Map structure.
 */
void place_player(Map *map);

/**
 * @brief Places the player in a new level.
 * @param map Pointer to the Map structure for the new level.
 */
void place_player_in_new_level(Map *map);

/**
 * @brief Initializes the player's properties at game start.
 * @param map Pointer to the Map structure for initial placement.
 */
void player_setup(Map *map);

/**
 * @brief Moves the player based on input character.
 * @param ch Input character for movement direction.
 * @param player Pointer to the Player structure.
 * @param map Pointer to the Map structure.
 */
void move_player(int ch, Player *player, Map *map);

/**
 * @brief Optimizes and redraws the player and the tile they are on.
 * @param player Pointer to the Player structure.
 * @param tile_under_player Tile character under the player.
 * @param map Pointer to the Map structure.
 */
void optimized_redraw(Player *player, char *tile_under_player, Map *map);

/**
 * @brief Draws the player's current status on the screen.
 * @param player Pointer to the constant Player structure.
 */
void draw_player_status(const Player *player);

#endif // PLAYER_H
