#include "src/Game.hpp"

int main() {
  srand(time(0));

  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  wrefresh(stdscr);

  Rush::Game game;
  game.run();

  delwin(stdscr);
  endwin();

  return EXIT_SUCCESS;
}
