#include <ncurses.h>

int main() {
  // Initialize the screen
  initscr();

  // Make sure the terminal supports colors
  if (!has_colors()) {
    endwin();
    printf("Your terminal does not support color\n");
    return 1;
  }
  // Start colors in ncurses
  start_color();
  // Define some color pairs
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);

  // Allow for extended keyboard (like F1, F2 keys etc.)
  keypad(stdscr, TRUE);
  // Do not echo keypresses to the screen
  noecho();
  // Hide the cursor
  curs_set(0);

  // Set up the screen for a dungeon crawler
  // TODO: Replace this with actual game initialization code
  printw("Welcome to the Dungeon Crawler!");

  // Use a color pair
  attron(COLOR_PAIR(1));
  printw(" This text is red on black.");
  attroff(COLOR_PAIR(1));

  // Refresh the screen to see changes
  refresh();
  // Wait for user input
  getch();

  // End ncurses mode
  endwin();

  return 0;
}
