#include "game_control.h"

void pause_game(void) {
  attron(COLOR_PAIR(COLOR_PAIR_GAME_TEXT));
  mvprintw(0, 0, "Game paused. Press 'p' to resume.");
  attroff(COLOR_PAIR(COLOR_PAIR_GAME_TEXT));
  refresh();

  while (getch() != 'p') {
    // Wait for 'p' to be pressed again
  }

  // Clear only the message area, not the entire screen
  move(0, 0);
  clrtoeol(); // This is a neat feature!
}

bool confirm_quit(void) {
  attron(COLOR_PAIR(COLOR_PAIR_GAME_TEXT));
  mvprintw(0, 0, "Are you sure you want to quit? (y/n)");
  attroff(COLOR_PAIR(COLOR_PAIR_GAME_TEXT));
  refresh();

  char ch = getch();
  return (ch == 'y' || ch == 'Y');
}
