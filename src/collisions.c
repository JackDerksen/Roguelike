#include "collisions.h"

// Assuming '#' represents a wall and '.' represents a walkable tile
bool check_collision(Map *map, int newX, int newY) {
  // Check map boundaries first
  if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT) {
    return true; // Position is out of bounds
  }

  // Check if the tile is walkable
  if (map->tiles[newY][newX] == '#') {
    return true; // Position is a wall, hence not walkable
  }

  return false; // Position is within bounds and not a wall, hence walkable
}
