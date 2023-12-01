#ifndef ORC_H
#define ORC_H

#include "collisions.h"
#include "map.h"
#include "player.h"
#include "splash.h"
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
  bool is_alive;
} Orc;

extern Orc orcs[];
extern int num_orcs;

void initialize_orcs(void);
void place_orcs(Map *map);
bool is_space_occupied_by_orc(int x, int y, int excluding_orc_index);
bool is_space_occupied_by_player(int x, int y, Player *player);
bool is_adjacent(Player *player, Orc *orc);
int manhattan_distance(int x1, int y1, int x2, int y2);
void move_orcs_towards_player(Player *player, Map *map, int frame_counter);

#endif // ORC_H
