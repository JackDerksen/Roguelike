#include "game_control.h"

/**
 * @brief Pauses the game until the player presses 'p'.
 *
 * This function halts the game execution and waits for the player to press 'p'
 * to resume the game. During the pause, a message is displayed to inform the
 * player how to resume.
 */
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

/**
 * @brief Confirms with the player before quitting the game.
 *
 * Asks the player if they are sure about quitting the game.
 * It waits for the player's input and returns true if the player confirms the
 * quit action. Specifically, it checks for 'y' or 'Y' as the confirmation
 * input.
 *
 * @return True if the player confirms to quit, otherwise false.
 */
bool confirm_quit(void) {
  attron(COLOR_PAIR(COLOR_PAIR_GAME_TEXT));
  mvprintw(0, 0, "Are you sure you want to quit? (y/n)");
  attroff(COLOR_PAIR(COLOR_PAIR_GAME_TEXT));
  refresh();

  char ch = getch();
  return (ch == 'y' || ch == 'Y');
}
