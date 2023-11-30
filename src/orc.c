#include "orc.h"

extern Player player;

Orc orcs[MAX_ORCS];
int num_orcs;

void initialize_orcs(void) {
  num_orcs = (rand() % 5) + 4; // Random number between 4 and 8

  for (int i = 0; i < num_orcs; i++) {
    orcs[i].x = -1;
    orcs[i].y = -1;
    orcs[i].health = 100;
    orcs[i].max_health = 100;
    orcs[i].damage = 10;
  }
}

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

// Include other orc-related functions here (for future steps)

