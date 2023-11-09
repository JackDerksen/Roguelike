#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <ncurses.h>

#define START_X 10
#define START_Y 10
#define MAX_HEALTH 100

typedef struct {
  int x, y; // Position on the map
  int health;
  // Other character attributes
} Character;

void initialize_character(Character *character);
void draw_character(const Character *character);
void player_setup(void);

#endif // CHARACTERS_H
