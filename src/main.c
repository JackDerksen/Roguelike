#include <curses.h>
#include <ncurses.h>

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

  map_setup();
  player_setup();

  show_splash_screen();

  bool game_running = true;
  while (game_running) {
    draw_map(&game_map);
    attron(COLOR_PAIR(3));
    mvprintw(player.y, player.x, "@");
    attroff(COLOR_PAIR(3));
    refresh();

    int ch = getch();

    switch (ch) {
    case KEY_UP:
      if (!check_collisions(player.x, player.y - 1)) {
        player.y--;
      }
      break;
    case KEY_DOWN:
      if (!check_collisions(player.x, player.y + 1)) {
        player.y++;
      }
      break;
    case KEY_LEFT:
      if (!check_collisions(player.x - 1, player.y)) {
        player.x--;
      }
      break;
    case KEY_RIGHT:
      if (!check_collisions(player.x + 1, player.y)) {
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
