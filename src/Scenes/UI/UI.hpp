#ifndef UI_HPP
#define UI_HPP

#include <ncurses.h>
#include <string>

#include "../../Scenes/Scene.hpp"

namespace Rush {

class UI : public Scene {
 protected:
  int score;
  bool press_enter(const int key_pressed);
  bool press_esc(const int key_pressed);

 public:
  UI(const Screen& screen);
  void game_over();
  void initial_screen();

  // SETTERS
  void set_score(int score);
};

}  // namespace Rush

#endif