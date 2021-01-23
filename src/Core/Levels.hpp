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

 protected:
  Level* head;
  void prepend();

 public:
  Levels(const Levels& other);
  Levels(const Screen& map_screen, const Grid& map_grid);
  ~Levels();
  Level& get_prev();
  Level& get_curr();
  Level& get_next();

#if DEBUG == 1
  void print();
#endif
};

}  // namespace Rush

#endif
