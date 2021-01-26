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

 public:
  Game();
  ~Game();
  void run();
};

}  // namespace Rush

#endif
