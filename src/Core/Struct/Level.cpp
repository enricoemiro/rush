#include "Level.hpp"

namespace Rush {

Level::Level(int value, const Screen& map_screen, const Grid& map_grid)
    : value(value),
      map(new Map(map_screen, map_grid)),
      t_enemies(new Enemy(this->map->get_screen_window(),
                          map_grid,
                          Constants::Game::TENEMY_CHAR)),
      m_enemies(new MEnemy(this->map->get_screen_window(),
                           map_grid,
                           Constants::Game::MENEMY_CHAR)),
      prev(nullptr),
      next(nullptr) {}

Level::~Level() {
  delete this->map;
  delete this->t_enemies;
  delete this->m_enemies;
}

}  // namespace Rush
