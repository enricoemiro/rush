#ifndef GAME_HPP
#define GAME_HPP

#include "Core/Levels.hpp"
#include "Core/Player.hpp"
#include "Scenes/Game/Status.hpp"

namespace Rush {

class Game {
 private:
  Levels* levels;
  Player* player;
  Status* status;
  void init_level(Level_Ptr& level);
  void go_next(Level_Ptr& level);
  void go_prev(Level_Ptr& level);
  void draw_spawn(Level_Ptr& level);
  void draw_exit(Level_Ptr& level);
  void draw_spawn_exit_point(Level_Ptr& level);

  /** Helpers */
  char get_character(Level_Ptr& level, const Coordinate& coordinate);
  void add_character(Level_Ptr& level,
                     const Coordinate& coordinate,
                     const char ch);
  /***********/

 public:
  Game();
  ~Game();
  void run();
};

}  // namespace Rush

#endif
