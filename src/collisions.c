#include "collisions.h"

// Assuming '#' represents a wall and '.' represents a walkable tile
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
