#include <iostream>

#include "src/Game.hpp"

int main() {
  srand(time(0));

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  wrefresh(stdscr);

  Rush::Game game;
  game.run();

  delwin(stdscr);
  endwin();

  return EXIT_FAILURE;
}
