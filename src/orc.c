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

// Calculate Manhattan distance between two points
int manhattan_distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

void move_orcs_towards_player(Player *player, Map *map) {
  // The orc will only move if the player is this close
  const int ORC_MOVEMENT_THRESHOLD = 10;

  for (int i = 0; i < num_orcs; i++) {
    if (manhattan_distance(player->x, player->y, orcs[i].x, orcs[i].y) <=
        ORC_MOVEMENT_THRESHOLD) {
      int dx = (player->x > orcs[i].x) ? 1 : (player->x < orcs[i].x) ? -1 : 0;
      int dy = (player->y > orcs[i].y) ? 1 : (player->y < orcs[i].y) ? -1 : 0;

      // Ensure orc doesn't walk into walls or other obstacles
      if (!check_collision(map, orcs[i].y + dy, orcs[i].x + dx)) {
        orcs[i].x += dx;
        orcs[i].y += dy;
      }
    }
  }
}
