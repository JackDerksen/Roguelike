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
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
  }

  // Allow for extended keyboard (like F1, F2 keys etc.)
  keypad(stdscr, TRUE);
  // Do not echo keypresses to the screen
  noecho();
  // Hide the cursor
  curs_set(0);

  // Set up the screen for a dungeon crawler
  // TODO: Replace this with actual game initialization code
  printw("Welcome to Jack's Dungeon Crawler! Press the 'q' key to exit.");

  // Use a colour pair
  attron(COLOR_PAIR(1));
  printw(" This text is red on black.");
  attroff(COLOR_PAIR(1));

  // Refresh the screen to see changes
  refresh();

  return 0;
}
