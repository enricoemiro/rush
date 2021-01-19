#include <iostream>

#include "src/Core/Levels.hpp"
#include "src/Core/Player.hpp"
#include "src/Core/Struct/Coordinate.hpp"
#include "src/Core/Struct/Grid.hpp"
#include "src/Core/Struct/Screen.hpp"
#include "src/Game.hpp"

int main() {
  srand(time(0));

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  wrefresh(stdscr);

  Rush::Levels levels(Rush::Screen(Rush::Grid(40, 32), Rush::Coordinate(0, 0)),
                      Rush::Grid(10, 8));
  Rush::Player player('&');
  Rush::Game game(levels, '&', 3);

  game.run();

  delwin(stdscr);
  endwin();

  return 0;
}
