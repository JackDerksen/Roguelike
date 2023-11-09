#include <stdbool.h>

#include "collisions.h"

bool check_collisions(int newX, int newY) {
  if (newX < 0 || newY < 0 || newX >= MAP_WIDTH || newY >= MAP_HEIGHT) {
    return true; // There was a collision with the boundary
  }

  // char tile = FIELD[newX][newY];
  // if (tile == TILE_WALL) { // Or some other obstacle
  //  return true;
  //  }
  //
  return false;
}
