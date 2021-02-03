#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "../../Scenes/Game/Map.hpp"
#include "../Enemies/Enemy.hpp"
#include "../Enemies/MEnemy.hpp"
#include "Coordinate.hpp"
#include "Screen.hpp"

namespace Rush {

struct Level {
  int value;
  Map* map;
  Enemy* t_enemies;
  MEnemy* m_enemies;
  Level* prev;
  Level* next;

  Level(int value, const Screen& map_screen, const Grid& map_grid);
  ~Level();
};

typedef Level* Level_Ptr;

}  // namespace Rush

#endif
