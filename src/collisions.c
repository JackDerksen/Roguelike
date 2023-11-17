#include "collisions.h"

bool check_collision(Map *map, int newY, int newX) {
  // Check map boundaries
  if (newY < 0 || newY >= MAP_HEIGHT || newX < 0 || newX >= MAP_WIDTH) {
    return true; // Out of bounds
  }

  // Check if the tile is walkable
  return map->tiles[newY][newX] == '#'; // '#' represents a wall
}
