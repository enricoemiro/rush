#include "Status.hpp"

namespace Rush {

Status::Status(const Screen& screen, int& level, int& score, int& lives)
    : Scene(screen), level(level), score(score), lives(lives) {
  EXIT_IF_TRUE(this->screen.size.height < 3,
               "The status screen must have a minimum height of 3");
}

void Status::draw() {
  this->draw_edges();
  mvwprintw(this->screen.window, 1, 1, "Level: %d", this->level);
  mvwprintw(this->screen.window, 2, 1, "Score: %d", this->score);
  mvwprintw(this->screen.window, 3, 1, "Lives: %d", this->lives);
  this->refresh();
}

}  // namespace Rush
