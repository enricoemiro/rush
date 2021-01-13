#ifndef SCENE_HPP
#define SCENE_HPP

#include <ncurses.h>

struct Screen {
  int width,
      height,
      start_x,
      start_y;
  WINDOW *window;

  Screen(int width,
         int height,
         int start_x,
         int start_y) : width(width),
                        height(height),
                        start_x(start_x),
                        start_y(start_y),
                        window(newwin(height + 2, width + 2, start_y, start_x)) {}

  ~Screen() {
    if (this->window) {
      delwin(this->window);
      this->window = nullptr;
    }
  }
};

class Scene {
 protected:
  Screen *screen;
  void refresh();
  void draw_edges();

 public:
  Scene(Screen *);
  void draw();
};

#endif
