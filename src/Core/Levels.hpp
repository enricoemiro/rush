#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "../Scenes/Game/Map.hpp"
#include "Struct/Grid.hpp"
#include "Struct/Screen.hpp"

struct Level {
  int value;
  Map *map;
  Level *prev;
  Level *next;

  Level();
};

class Levels {
 protected:
  Screen *screen;
  Grid *grid;
  Level *head;
  void insert_at_head();

 public:
  Levels(Screen *screen, Grid *grid);
  ~Levels();
  Level *prev_level();
  Level *curr_level();
  Level *next_level();

#if DEBUG == 1
  void print();
#endif
};

#endif
