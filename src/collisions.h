#ifndef COLLISION_H
#define COLLISION_H

#include "map.h"

/**
 * @brief Checks if the next position is an invalid tile.
 * @param map Pointer to the map structure
 * @param new_y Integer representing the y position of the tile being moved to.
 * @param new_x Integer representing the x position of the tile being moved to.
 * @return True if there is a collision, false otherwise.
 */
bool check_collision(Map *map, int new_y, int new_x);

#endif // COLLISION_H
