#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "../Scenes/Game/Map.hpp"
#include "Enemies/Enemy.hpp"
#include "Enemies/MEnemy.hpp"
#include "Struct/Grid.hpp"
#include "Struct/Screen.hpp"

namespace Rush {

class Levels {
 private:
  // Struct level
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

  Screen map_screen;
  Grid map_grid;
  Level* head;
  void prepend();

 public:
  Levels(const Screen& map_screen, const Grid& map_grid);
  ~Levels();

  // Getters / Setters
  void set_head_to_prev();
  void set_head_to_next();

  int get_value();
  Map* get_map();
  Enemy* get_t_enemies();
  MEnemy* get_m_enemies();
};

}  // namespace Rush

#endif
