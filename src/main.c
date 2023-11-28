#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include "characters.h"
#include "collisions.h"
#include "game_control.h"
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
    if (first_render) {
      render_map(&game_map);
      first_render = false;
      tile_under_player = game_map.tiles[player.y][player.x];
    }

    draw_character_status(&player);

    attron(COLOR_PAIR(3));
    mvprintw(player.y, player.x, "@");
    attroff(COLOR_PAIR(3));

    // Get/handle inputs
    int ch = getch();

    if (ch == 'p') {
      pause_game();
      first_render = true;
    } else if (ch == 'q') {
      if (confirm_quit()) {
        game_running = false;
      } else {
        first_render = true;
      }
    } else {
      move_player(ch, &player, &game_map);

      if (player.move_counter >= 3) {
        move(MAP_HEIGHT, 0);
        clrtoeol();
        player.move_counter = 0;
      }
    }

    // Check if the player reached the exit
    if (game_map.tiles[player.y][player.x] == 'E') {
      generate_map(&game_map);
      place_player_in_new_level(&game_map);
      first_render = true;
    }

    // Get loot from a chest
    if (game_map.tiles[player.y][player.x] == 'C') {
      LootType loot = generate_random_loot();
      handle_loot(&player, loot);

      // Replace the now looted chest with a floor tile
      game_map.tiles[player.y][player.x] = '.';
      optimized_redraw(&player, &tile_under_player, &game_map);
    }

    // Redraw only the tile that was under the player
    optimized_redraw(&player, &tile_under_player, &game_map);

    refresh();
  }

  endwin();
  return 0;
}
