#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <ncurses.h>

struct Screen {
  int width, height,
      start_x, start_y;
  WINDOW *window;

  Screen(int width, int height,
         int start_x, int start_y);
  ~Screen();
};

#endif
