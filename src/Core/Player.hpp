#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <ncurses.h>

#include "../Scenes/Game/Map.hpp"
#include "Struct/Coordinate.hpp"

namespace Rush {

class Player {
 private:
  WINDOW* map_window;

 protected:
  char symbol;
  Coordinate current;
  Coordinate previous;

 protected:
  void jump(const Coordinate& next, bool& has_jumped);
  void jump_up();
  void jump_down();

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
