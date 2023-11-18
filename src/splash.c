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
  printw("                            Press any key to start.\n");
  printw("\n");
  printw("                            Press 'q' to quit, and\n");
  printw("                            use arrow keys to move.\n");
  refresh();
  getch();
}
