#ifndef STATUS_HPP
#define STATUS_HPP

#include "../../Core/Struct/Screen.hpp"
#include "../../Utilities/Macros.hpp"
#include "../Scene.hpp"

namespace Rush {

class Status : public Scene {
 private:
  int level;
  int score;
  int lives;
  bool is_over;

 public:
  Status(const Screen& screen, int level, int score, int lives);
  void draw();
  void increment_score(int score);
  void increment_lives();
  void decrement_lives();
  bool get_is_over() const;
  void set_level(int level);
};

}  // namespace Rush

#endif
