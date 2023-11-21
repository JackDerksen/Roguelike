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
char tile_under_player = '.';

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
  bool first_render = true;

  while (game_running) {

    int old_x = player.x;
    int old_y = player.y;

    // Render the map using an absurdly dense block of code
    if (first_render) {
      for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
          if (game_map.tiles[y][x] == '#') {
            attron(COLOR_PAIR(COLOR_PAIR_WALLS));
            mvprintw(y, x, "#");
            attroff(COLOR_PAIR(COLOR_PAIR_WALLS));
          } else if (game_map.tiles[y][x] == '.') {
            attron(COLOR_PAIR(COLOR_PAIR_FLOORS));
            mvprintw(y, x, ".");
            attroff(COLOR_PAIR(COLOR_PAIR_FLOORS));
          } else if (game_map.tiles[y][x] == 'E') {
            attron(COLOR_PAIR(COLOR_PAIR_EXIT));
            mvprintw(y, x, "E");
            attroff(COLOR_PAIR(COLOR_PAIR_EXIT));
          } else if (game_map.tiles[y][x] == 'C') {
            attron(COLOR_PAIR(COLOR_PAIR_CHEST));
            mvprintw(y, x, "C");
            attroff(COLOR_PAIR(COLOR_PAIR_CHEST));
          }
        }
      }
      first_render = false;
      tile_under_player = game_map.tiles[player.y][player.x];
    }

    attron(COLOR_PAIR(3));
    mvprintw(player.y, player.x, "@"); // Cute little guy, eh?
    attroff(COLOR_PAIR(3));
    refresh();

    // Get/handle inputs
    int ch = getch();

    switch (ch) {
    case KEY_UP:
      if (!check_collision(&game_map, player.y - 1, player.x)) {
        player.y--;
      }
      break;
    case KEY_DOWN:
      if (!check_collision(&game_map, player.y + 1, player.x)) {
        player.y++;
      }
      break;
    case KEY_LEFT:
      if (!check_collision(&game_map, player.y, player.x - 1)) {
        player.x--;
      }
      break;
    case KEY_RIGHT:
      if (!check_collision(&game_map, player.y, player.x + 1)) {
        player.x++;
      }
      break;

    // Adding some vim movement keybinds because why not
    case 'k':
      if (!check_collision(&game_map, player.y - 1, player.x)) {
        player.y--;
      }
      break;
    case 'j':
      if (!check_collision(&game_map, player.y + 1, player.x)) {
        player.y++;
      }
      break;
    case 'h':
      if (!check_collision(&game_map, player.y, player.x - 1)) {
        player.x--;
      }
      break;
    case 'l':
      if (!check_collision(&game_map, player.y, player.x + 1)) {
        player.x++;
      }
      break;

    case 'q':
      game_running = false;
      break;
    }

    // Redraw the tile that was under the player
    char old_tile_char =
        (old_x == player.x && old_y == player.y) ? '@' : tile_under_player;
    if (old_tile_char == 'C') {
      attron(COLOR_PAIR(COLOR_PAIR_CHEST));
    } else {
      attron(COLOR_PAIR(COLOR_PAIR_FLOORS));
    }
    mvprintw(old_y, old_x, "%c", old_tile_char);
    attroff(COLOR_PAIR(COLOR_PAIR_CHEST));
    attroff(COLOR_PAIR(COLOR_PAIR_FLOORS));

    // Update tile_under_player before redrawing the player
    tile_under_player = game_map.tiles[player.y][player.x];

    // Draw the player at the new position
    attron(COLOR_PAIR(3));
    mvprintw(player.y, player.x, "@");
    attroff(COLOR_PAIR(3));

    refresh();

    // Check if the player reached the exit
    if (game_map.tiles[player.y][player.x] == 'E') {
      generate_map(&game_map);
      player_setup(&game_map);
      first_render = true;
      continue;
    }

    // TODO: Add chest looting/interaction logic here later
  }

  endwin();
  return 0;
}
