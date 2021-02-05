#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include "Core/Levels.hpp"
#include "Core/Player.hpp"
#include "Scenes/Game/Status.hpp"
#include "Scenes/UI/UI.hpp"

namespace Rush {

class Game {
 private:
  Levels* levels;
  Player* player;
  Status* status;
  UI* ui;
  void init_level();
  void go_next();
  void go_prev();
  void draw_spawn();
  void draw_exit();

  /** Helpers */
  char get_character(const Coordinate& coordinate);
  void add_character(const Coordinate& coordinate, const char ch);
  /***********/

 public:
  Game();
  ~Game();
  void run();
};

}  // namespace Rush

#endif
