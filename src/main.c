#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include "attacking.h"
#include "game_control.h"
#include "loot.h"
#include "map.h"
#include "orc.h"
#include "player.h"
#include "setup.h"
#include "splash.h"

// Global variables
Map game_map;
Player player;
char tile_under_player = '.';
int frame_counter = 0;

/**
 * @brief The main function, contains the game loop.
 *
 * This is the main function of the game, where most other game logic is called.
 * It contains the game loop which will run infinitely until the game crashes or
 * the player quits.
 *
 * @return 0 if the game exited successfully (ie. on purpose, no crashes).
 */
int main(void) {
  if (screen_setup() != 0) {
    return 1;
  }

  // Seed the random map generator
  srand((unsigned)time(NULL));

  initialize_map(&game_map);
  generate_map(&game_map);
  player_setup(&game_map);
  initialize_orcs();
  place_orcs(&game_map);
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

    draw_player_status(&player);

    attron(COLOR_PAIR(COLOR_PAIR_BLUE));
    mvprintw(player.y, player.x, "@");
    attroff(COLOR_PAIR(COLOR_PAIR_BLUE));

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

      // Player's attack phase
      if (ch == ' ') {
        for (int i = 0; i < num_orcs; i++) {
          if (is_adjacent(&player, &orcs[i])) {
            player_attack_orc(&player, &orcs[i]);
            break;
          }
        }
      }

      if (player.move_counter >= 3) {
        clear_dialogue();
        player.move_counter = 0;
      }
    }

    // Check if the player reached the exit
    if (game_map.tiles[player.y][player.x] == 'E') {
      generate_map(&game_map);
      place_player_in_new_level(&game_map);
      initialize_orcs();
      place_orcs(&game_map);
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

    // Orcs' movement and attack phase
    move_orcs_towards_player(&player, &game_map, frame_counter);

    render_map(&game_map);
    // Redraw only the tile that was under the player
    optimized_redraw(&player, &tile_under_player, &game_map);

    frame_counter++;
    refresh();
  }

  endwin();
  return 0;
}
