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
  int lives;
  int score;
  bool is_over;

 public:
  Game();
  ~Game();
  void run();
};

}  // namespace Rush

#endif
