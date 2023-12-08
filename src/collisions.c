#include "collisions.h"

/**
 * @brief Checks if the next position is an invalid tile.
 *
 * Return true (there was a collision) if the next tile the player or orc will
 * collide with is a wall tile, which should not be walkable, or the position is
 * out of bounds.
 *
 * @param map Pointer to the map structure
 * @param new_y Integer representing the y position of the tile being moved to.
 * @param new_x Integer representing the x position of the tile being moved to.
 * @return True if there is a collision, false otherwise.
 */
bool check_collision(Map *map, int new_y, int new_x) {
  // Check map boundaries first
  if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT) {
    return true; // Position is out of bounds
  }

  // Check if the tile is walkable
  if (map->tiles[new_y][new_x] == '#') {
    return true; // Position is a wall, hence not walkable
  }

  return false; // Position is within bounds and not a wall, hence walkable
}
