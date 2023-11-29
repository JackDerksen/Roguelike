#ifndef PLAYERS_H
#define PLAYERS_H

#include "collisions.h"
#include "map.h"
#include <ncurses.h>

#define PLAYER_START_X 10
#define PLAYER_START_Y 10

typedef struct {
  int x, y; // Current position on the map
  int old_x, old_y;
  int health;
  int max_health;
  int armour;
  int max_armour;
  int damage;
  int move_counter;
  bool has_sword;
} Player;

void draw_player(const Player *player);
void place_player(Map *map);
void place_player_in_new_level(Map *map);
void player_setup(Map *map);
void move_player(int ch, Player *player, Map *map);
void optimized_redraw(Player *player, char *tile_under_player, Map *map);
void draw_player_status(const Player *player);

#endif // PLAYERS_H
