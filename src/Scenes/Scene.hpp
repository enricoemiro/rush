#ifndef SCENE_HPP
#define SCENE_HPP

#include <ncurses.h>

#include "../Core/Struct/Screen.hpp"

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
