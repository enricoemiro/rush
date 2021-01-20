#ifndef GAME_HPP
#define GAME_HPP

#include "Core/Levels.hpp"
#include "Core/Player.hpp"

namespace Rush {

class Game {
 private:
  Levels levels;
  Player player;
  int lives;
  int score;
  bool is_over;

 public:
  Game(const Levels &levels,
       const Player &player,
       int lives);
  void run();
};

}  // namespace Rush

#endif
