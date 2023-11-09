#include <ncurses.h>

#include "map.h"

// This module should handle everything related to the game map — such as
// generating the layout, managing rooms and tiles, and handling interactions
// with the map.
//
// In map.h, declare structures for the map and any public functions. In map.c,
// define these functions. The map_setup() function in setup.c should call an
// initialization function from this module to set up the map.

extern Map game_map;

void draw_map(const Map *map) {
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      mvprintw(y, x, "%c", map->tiles[y][x]);
    }
  }
}

void map_setup(void) {
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      game_map.tiles[y][x] =
          (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1) ? '#'
                                                                          : '.';
    }
  }
}
