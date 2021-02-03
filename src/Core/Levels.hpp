#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "../Scenes/Game/Map.hpp"
#include "Struct/Grid.hpp"
#include "Struct/Level.hpp"
#include "Struct/Screen.hpp"

namespace Rush {

class Levels {
 private:
  Screen map_screen;
  Grid map_grid;
  Level_Ptr head;
  void prepend();

 public:
  Levels(const Levels& other);
  Levels(const Screen& map_screen, const Grid& map_grid);
  ~Levels();
  Level_Ptr get_prev();
  Level_Ptr get_curr();
  Level_Ptr get_next();
};

}  // namespace Rush

#endif
