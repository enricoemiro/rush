#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <ncurses.h>
#include <stdlib.h>
#include <vector>

#include "../../Core/Struct/Coordinate.hpp"
#include "../../Core/Struct/Grid.hpp"
#include "../../Core/Struct/Room.hpp"
#include "../../Utilities/Constants.hpp"

namespace Rush {

class Enemy {
 protected:
  WINDOW* map_window;
  Grid grid;
  char symbol;
  int level;
  std::vector<Room> rooms;
  bool was_drawn;
  void select_y(int room_index);
  void select_x(int room_index, int y_index);
  virtual void spawn_conditions(const Coordinate& coordinate);
  char get_character(const Coordinate& coordinate);
  void print_character(const Coordinate& coordinate, const char ch);

  /** Helpers */
	bool is_space(const char ch);
  bool is_walkable(const char ch);
  /***********/

 public:
  Enemy(WINDOW* map_window, const Grid& grid, char symbol);
  void draw();

  // SETTERS
  void set_rooms(const std::vector<Room>& rooms);
  void set_level(int level);
};

}  // namespace Rush

#endif
