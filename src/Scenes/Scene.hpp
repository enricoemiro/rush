#ifndef SCENE_HPP
#define SCENE_HPP

#include <ncurses.h>

struct Screen {
  unsigned int width,
      height,
      start_x,
      start_y;
  WINDOW *window;

  Screen(unsigned int width,
         unsigned int height,
         unsigned int start_x,
         unsigned int start_y) : width(width),
                                 height(height),
                                 start_x(start_x),
                                 start_y(start_y),
                                 window(newwin(height + 2, width + 2, start_y, start_x)) {}
};

class Scene {
 protected:
  Screen *screen;
  void refresh();
  void draw_edges();

 public:
  Scene(Screen *);
  ~Scene();
  void draw();
};

#endif
