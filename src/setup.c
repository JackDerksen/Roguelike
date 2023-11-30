#include "setup.h"

int screen_setup(void) {
  initscr();

  if (has_colors()) {
    // Start colours in ncurses if the user's terminal supports it
    start_color();
    init_pair(COLOR_PAIR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_PAIR_WALLS, COLOR_WHITE, COLOR_WHITE);
    init_pair(COLOR_PAIR_FLOORS, COLOR_BLACK, COLOR_BLACK);
    init_pair(COLOR_PAIR_EXIT, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOR_PAIR_CHEST, COLOR_BLACK, COLOR_YELLOW);
    init_pair(COLOR_PAIR_GAME_TEXT, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_PAIR_HEALTH, COLOR_RED, COLOR_RED);
    init_pair(COLOR_PAIR_ARMOUR, COLOR_GREEN, COLOR_GREEN);
    init_pair(COLOR_PAIR_ORC, COLOR_BLACK, COLOR_RED);
  }

  // Allow for extended keyboard (like F1, F2 keys etc.)
  keypad(stdscr, TRUE);
  // Do not echo keypresses to the screen
  noecho();
  // Hide the cursor
  curs_set(0);

  refresh();

  return 0;
}
