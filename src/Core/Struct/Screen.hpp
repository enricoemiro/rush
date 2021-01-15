#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <ncurses.h>

#include "./Coordinate.hpp"
#include "./Grid.hpp"

namespace Rush {

struct Screen {
  Grid size;
  Coordinate start;
  WINDOW *window;

  Screen(const Grid &size,
         const Coordinate &start);
  Screen(const Screen &other);
  ~Screen();
};

}  // namespace Rush

#endif
