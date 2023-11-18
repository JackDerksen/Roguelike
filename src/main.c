#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "characters.h"
#include "collisions.h"
#include "loot.h"
#include "map.h"
#include "setup.h"
#include "splash.h"

// Global variables
Map game_map;
Character player;

int main(void) {
  if (screen_setup() != 0) {
    return 1;
  }

  // Seed the random map generator
  srand((unsigned)time(NULL));

  initialize_map(&game_map);
  generate_map(&game_map);
  player_setup(&game_map);
  show_splash_screen();

  // --------------- Game Loop --------------- //
  bool game_running = true;
  while (game_running) {
    // Clear the screen, or the relevant portion of it
    // Render the map
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        mvprintw(y, x, "%c", game_map.tiles[y][x]);
      }
    }
    attron(COLOR_PAIR(3));
    mvprintw(player.y, player.x, "@");
    attroff(COLOR_PAIR(3));
    refresh();

    int ch = getch();

    switch (ch) {
    case KEY_UP:
      if (!check_collision(&game_map, player.x, player.y - 1)) {
        player.y--;
      }
      break;
    case KEY_DOWN:
      if (!check_collision(&game_map, player.x, player.y + 1)) {
        player.y++;
      }
      break;
    case KEY_LEFT:
      if (!check_collision(&game_map, player.x - 1, player.y)) {
        player.x--;
      }
      break;
    case KEY_RIGHT:
      if (!check_collision(&game_map, player.x + 1, player.y)) {
        player.x++;
      }
      break;
    case 'q':
      game_running = false;
      break;
    }
    clear();
    // Update the game state
    // Render to screen
  }

  // Clean up before exiting
  endwin();

  return 0;
}
