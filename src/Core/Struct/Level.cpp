#include "Level.hpp"

namespace Rush {

Level::Level(int value,
             const Screen& map_screen,
             const Grid& map_grid)
    : value(value),
      map(new Map(map_screen, map_grid)),
      t_enemies(new Enemy(this->map->get_screen_window(), map_grid, 'T')),
      prev(nullptr),
      next(nullptr) {}

}  // namespace Rush
