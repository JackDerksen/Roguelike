#include "splash.h"

void show_splash_screen(void) {
  clear();

  printw("                                  Welcome to...\n");
  printw("\n");

  // This may look like shit right now because of line wrapping, but it should
  // look good in game!

  const char *art[] = {
      "       _            _    _       _____                        _ _ _",
      "      | |          | |  ( )     |  __ \\                      | (_) |",
      "      | | __ _  ___| | _|/ ___  | |__) |___   __ _ _   _  ___| |_| | "
      "_____",
      "  _   | |/ _` |/ __| |/ / / __| |  _  // _ \\ / _` | | | |/ _ \\ | | |/ "
      "/ _ \\",
      " | |__| | (_| | (__|   <  \\__ \\ | | \\ \\ (_) | (_| | |_| |  __/ | |  "
      " <  "
      "__/",
      "  \\____/ \\__,_|\\___|_|\\_\\ |___/ |_|  \\_\\___/ \\__, "
      "|\\__,_|\\___|_|_|_|\\_\\___|",
      "                                              __/ |",
      "                                             |___/",
      NULL};

  for (int i = 0; art[i] != NULL; ++i) {
    printw("%s\n", art[i]);
  }

  printw("\n");
  printw("                             Press any key to start.\n");
  printw("\n");
  printw("                              Reach the exit 'E'.\n");
  printw("\n");
  printw("                            Press 'q' to quit, and\n");
  printw("                            'p' to pause the game.\n");
  printw("                       Use the arrow keys or 'hjkl' to move.\n");
  printw("                        Orcs will hunt you down and try to\n");
  printw("                      kill you. Press 'space' to attack them!\n");
  refresh();
  getch();
}

void game_over_screen(void) {
  clear();

  printw("\n");

  // This may look like shit right now because of line wrapping, but it should
  // look good in game!

  const char *art[] = {
      "  ________                        ________",
      " /  _____/_____    _____   ____   \\_____  \\___  __ ___________",
      "/   \\  ___\\__  \\  /     \\_/ __ \\   /   |   \\  \\/ // __ \\_  __ "
      "\\",
      "\\    \\_\\  \\/ __ \\|  Y Y  \\  ___/  /    |    \\   /\\  ___/|  | "
      "\\/",
      " \\______  (____  /__|_|  /\\___  > \\_______  /\\_/  \\___  >__|",
      "        \\/     \\/      \\/     \\/          \\/          \\/",
      NULL};

  for (int i = 0; art[i] != NULL; ++i) {
    printw("%s\n", art[i]);
  }

  printw("\n");
  printw("                      Press any key to exit.\n");

  refresh();
  getch();
}
