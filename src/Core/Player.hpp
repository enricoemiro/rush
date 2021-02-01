#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <ncurses.h>

#include "../Scenes/Game/Map.hpp"
#include "../Scenes/Game/Status.hpp"
#include "../Utilities/Constants.hpp"
#include "Struct/Coordinate.hpp"

namespace Rush {

class Player {
 private:
  // Bullet struct
  struct Bullet {
    char direction;
    Coordinate current;
    Coordinate previous;

    Bullet(char direction, const Coordinate& current);
  };

  Status* status;
  char symbol;
  WINDOW* map_window;
  Coordinate current;
  Coordinate previous;
  std::vector<Bullet> bullets;
  void jump(const Coordinate& coordinate, bool& has_jumped);
  void jump_up();
  void jump_down();
  void collision(const Coordinate& coordinate);
  void update_bullets();
  void shoot_up(Coordinate& coordinate);
  void shoot_down(Coordinate& coordinate);

  /** Helpers */
  char get_character(const Coordinate& coordinate);
  void clear(const Coordinate& coordinate);
  bool is_right_edge(const Coordinate& coordinate);
  bool is_left_edge(const Coordinate& coordinate);
  bool is_double_block(const Coordinate& coordinate);
  bool is_enemy(const char ch);
  bool is_block(const char ch);
  bool is_floor(const char ch);
  bool is_wall(const char ch);
  bool is_flying(const char ch);
  /***********/

 public:
  Player(Status* status, char symbol);
  void move(int key_pressed);
  void shoot(int key_pressed);
  void draw();
  void draw_bullets();

  const Coordinate& get_coordinate();
  void set_coordinate(const Coordinate& coordinate);
  void set_window(WINDOW* map_window);
  void reset_coordinates();
  void reset_bullets();
};

}  // namespace Rush

#endif
