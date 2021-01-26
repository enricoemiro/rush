#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <ncurses.h>

#include "../Scenes/Game/Map.hpp"
#include "Struct/Coordinate.hpp"

namespace Rush {

class Player {
 private:
  char symbol;
  WINDOW* map_window;
  Coordinate current;
  Coordinate previous;
  void jump(const Coordinate& coordinate, bool& has_jumped);
  void jump_up();
  void jump_down();

  /** Helpers */
  char get_character(const Coordinate& coordinate);
  bool is_flying(const Coordinate& coordinate);
  bool is_right_edge(const Coordinate& coordinate);
  bool is_left_edge(const Coordinate& coordinate);
  bool is_block(const Coordinate& coordinate);
  bool is_double_block(const Coordinate& coordinate);
  bool is_wall(const Coordinate& coordinate);
  /***********/

 public:
  Player(char symbol);
  void move(int key_pressed);
  void draw();

  const Coordinate& get_coordinate();
  void set_coordinate(const Coordinate& coordinate);
  void set_window(WINDOW* map_window);
};

}  // namespace Rush

#endif
