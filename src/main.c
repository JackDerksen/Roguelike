#include <ncurses.h>

#include "characters.h"
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

  map_setup();
  player_setup();

  bool game_running = true;
  while (game_running) {
    draw_map(&game_map);
    mvprintw(player.y, player.x, "@");
    refresh();

    int ch = getch();

    switch (ch) {
    case KEY_UP:
      player.y--;
      break;
    case KEY_DOWN:
      player.y++;
      break;
    case KEY_LEFT:
      player.x--;
      break;
    case KEY_RIGHT:
      player.x++;
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
