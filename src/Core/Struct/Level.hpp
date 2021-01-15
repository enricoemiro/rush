#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "../../Scenes/Game/Map.hpp"
#include "Coordinate.hpp"
#include "Screen.hpp"

namespace Rush {

struct Level {
  int value;
  Map map;
  Level *prev;
  Level *next;

  Level(int value,
        const Screen &map_screen,
        const Grid &map_grid);
};

}  // namespace Rush

#endif
