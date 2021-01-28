#include "Level.hpp"

namespace Rush {

Level::Level(int value, const Screen& map_screen, const Grid& map_grid)
    : value(value),
      map(new Map(map_screen, map_grid)),
      prev(nullptr),
      next(nullptr) {}

}  // namespace Rush
