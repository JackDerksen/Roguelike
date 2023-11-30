#ifndef ORC_H
#define ORC_H

#include "collisions.h"
#include "map.h"
#include "player.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ORCS 8

typedef struct {
  int x, y;
  int old_x, old_y;
  int health;
  int max_health;
  int damage;
  int move_counter;
} Orc;

extern Orc orcs[];
extern int num_orcs;

void initialize_orcs(void);
void place_orcs(Map *map);

#endif // ORC_H
