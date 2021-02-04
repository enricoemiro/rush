#include "Status.hpp"

namespace Rush {

Status::Status(const Screen& screen, int level, int score, int lives)
    : Scene(screen), level(level), score(score), lives(lives), is_over(false) {
  EXIT_IF_TRUE(this->screen.size.height < 3,
               "The status screen must have a minimum height of 3");
}

void Status::resize(const std::vector<std::string>& messages) {
  for (std::size_t i = 0; i < messages.size(); ++i) {
    const std::string curr = messages.at(i);

    if (curr.size() > static_cast<std::size_t>(this->screen.size.width)) {
      this->screen.size.width = curr.size();
      wresize(this->screen.window, this->screen.size.height + 2,
              this->screen.size.width + 2);
    }
  }
}

void Status::print_messages(const std::vector<std::string>& messages) {
  wclear(this->screen.window);
  this->draw_edges();
  for (std::size_t i = 0; i < messages.size(); ++i) {
    const std::string curr = messages.at(i);

    mvwprintw(this->screen.window, i + 1, 1, curr.data());
  }
  this->refresh();
}

void Status::draw() {
  std::vector<std::string> messages = {"Level: " + std::to_string(this->level),
                                       "Score: " + std::to_string(this->score),
                                       "Lives: " + std::to_string(this->lives)};

  this->resize(messages);
  this->print_messages(messages);
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

int Status::get_score() {
  return this->score;
}

void Status::set_level(int level) {
  this->level = level;
  this->draw();
}

}  // namespace Rush
