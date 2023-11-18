#include <ncurses.h>

#include "characters.h"
#include "map.h"
#include "setup.h"

int screen_setup(void) {
  // Initialize the screen
  initscr();

  if (has_colors()) {
    // Start colours in ncurses if the user's terminal supports it
    start_color();
    init_pair(COLOR_PAIR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_PAIR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_PAIR_BLUE, COLOR_BLUE, COLOR_BLACK);
  }

  // Allow for extended keyboard (like F1, F2 keys etc.)
  keypad(stdscr, TRUE);
  // Do not echo keypresses to the screen
  noecho();
  // Hide the cursor
  curs_set(0);

  // Use a colour pair
  attron(COLOR_PAIR(1));
  printw(" This text is red on black.");
  attroff(COLOR_PAIR(1));

  // Refresh the screen to see changes
  refresh();

  return 0;
}
