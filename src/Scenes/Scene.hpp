#ifndef SCENE_HPP
#define SCENE_HPP

#include <ncurses.h>

#include "../Core/Struct/Screen.hpp"

namespace Rush {

class Scene {
 protected:
  Screen screen;
  void refresh();
  void draw_edges();

 public:
  Scene(const Screen &screen);
  void draw();
};

}  // namespace Rush

#endif
