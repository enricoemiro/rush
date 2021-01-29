#include "Status.hpp"

namespace Rush {

Status::Status(const Screen& screen, int level, int score, int lives)
    : Scene(screen), level(level), score(score), lives(lives), is_over(false) {
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

void Status::increment_score(int score) {
  this->score += score;
  this->draw();
}

void Status::increment_lives() {
  this->lives++;
  this->draw();
}

void Status::decrement_lives() {
  this->lives--;

  if (this->lives <= 0)
    this->is_over = true;

  this->draw();
}

bool Status::get_is_over() const {
  return this->is_over;
}

void Status::set_level(int level) {
  this->level = level;
  this->draw();
}

}  // namespace Rush
