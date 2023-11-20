#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "map.h"
#include <ncurses.h>

#define CHARACTER_START_X 10
#define CHARACTER_START_Y 10
#define CHARACTER_MAX_HEALTH 100

typedef struct {
  int x, y; // Position on the map
  int health;
} Character;

void initialize_character(Character *character);
void draw_character(const Character *character);
void place_player(Map *map);
void player_setup(Map *map);

#endif // CHARACTERS_H
