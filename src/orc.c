#include "orc.h"
#include "splash.h"
#include <curses.h>

extern Player player;

Orc orcs[MAX_ORCS];
int num_orcs;

void initialize_orcs(void) {
  num_orcs = (rand() % 5) + 4; // Random number between 4 and 8

  for (int i = 0; i < num_orcs; i++) {
    orcs[i].x = -1;
    orcs[i].y = -1;
    orcs[i].health = 40;
    orcs[i].max_health = 100;
    orcs[i].damage = 10;
    orcs[i].is_alive = true;
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

bool is_space_occupied_by_orc(int y, int x, int excluding_orc_index) {
  for (int i = 0; i < num_orcs; i++) {
    if (i != excluding_orc_index && orcs[i].x == x && orcs[i].y == y) {
      return true; // Another orc is already at this position
    }
  }
  return false;
}

bool is_space_occupied_by_player(int y, int x, Player *player) {
  return player->x == x && player->y == y;
}

bool is_adjacent_2(Player *player, Orc *orc) {
  return abs(player->x - orc->x) <= 1 && abs(player->y - orc->y) <= 1;
}

// I had to define this here for annoying reasons :/
void move_orcs_towards_player(Player *player, Map *map, int frame_counter) {
  const int ORC_MOVEMENT_THRESHOLD = 10;
  bool is_move_frame = (frame_counter % 2 == 0);

  for (int i = 0; i < num_orcs; i++) {
    // Skip the dead orcs
    if (!orcs[i].is_alive) {
      continue;
    }

    if (is_move_frame &&
        manhattan_distance(player->x, player->y, orcs[i].x, orcs[i].y) <=
            ORC_MOVEMENT_THRESHOLD) {
      if (is_adjacent_2(player, &orcs[i])) {
        // Orc attacks the player
        int damageDealt = orcs[i].damage;
        player->health -= damageDealt;

        if (player->health <= 0) {
          // Handle player defeat
          game_over_screen();
          int ch = getch();
          if (ch) {
            endwin(); // Close the ncurses window
            exit(0);  // Terminate the program
          }
        } else {
          // Display damage feedback
          mvprintw(MAP_HEIGHT, 2, "Orc hits you! Damage: %d, Your health: %d ",
                   damageDealt, player->health);
        }
      } else {
        // Determine the direction of movement
        int dx = (player->x > orcs[i].x) ? 1 : (player->x < orcs[i].x) ? -1 : 0;
        int dy = (player->y > orcs[i].y) ? 1 : (player->y < orcs[i].y) ? -1 : 0;

        // Calculate potential new position
        int new_x = orcs[i].x + dx;
        int new_y = orcs[i].y + dy;

        // Check if the new position is occupied by the player or is a collision
        if (!is_space_occupied_by_player(new_x, new_y, player) &&
            !check_collision(map, new_y, new_x)) {
          // Update orc's position
          orcs[i].x = new_x;
          orcs[i].y = new_y;
        }
      }
    }
  }
}
