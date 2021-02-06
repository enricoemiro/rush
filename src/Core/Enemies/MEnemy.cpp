#include "MEnemy.hpp"

namespace Rush {

MEnemy::MEnemy(WINDOW* map_window, const Grid& grid, char symbol)
    : Enemy(map_window, grid, symbol) {
  this->status = nullptr;
}

void MEnemy::update_enemies() {
  this->update_positions();
  this->draw_updated();
  wrefresh(this->map_window);
}

// Override of Enemy method
void MEnemy::spawn_conditions(const Coordinate& coordinate) {
  const char ch_1 = this->get_character(coordinate);
  const char ch_2 = this->get_character({coordinate.x, coordinate.y + 1});
  const char ch_3 = this->get_character({coordinate.x + 1, coordinate.y + 1});
  const char ch_4 = this->get_character({coordinate.x - 1, coordinate.y + 1});

  if (this->is_space(ch_1) && this->is_walkable(ch_2) &&
      rand() % 100 <= level * 1) {
    this->print_character(coordinate, this->symbol);

    if (this->is_walkable(ch_3) || this->is_walkable(ch_4))
      this->enemies.push_back({'R', coordinate, coordinate});
  }
}

// updating coordinate to make MEnemy move
void MEnemy::update_positions() {
  for (std::size_t i = 0; i < this->enemies.size(); ++i) {
    this->move_right(this->enemies.at(i));
    this->move_left(this->enemies.at(i));
    this->collision(this->enemies.at(i), i);
  }
}

// checking if there is a collision
void MEnemy::collision(SingleEnemy& enemy, int index) {
  const char ch_current = this->get_character(enemy.current);
  const char ch_M = this->get_character({enemy.current.x - 1, enemy.current.y});
  const char ch_P = this->get_character({enemy.current.x + 1, enemy.current.y});

  // collision with player
  if (ch_current == '&') {
    this->print_character(enemy.previous, ' ');
    this->status->decrement_lives();
    this->erase_enemy(index);
  }

  // collision with shoot
  if ((ch_current == '*') || (ch_M == '*') || (ch_P == '*')) {
    this->erase_enemy(index);
  }
}

// MEnemy moves to left
void MEnemy::move_left(SingleEnemy& enemy) {
  if (can_move_left(enemy)) {
    enemy.previous = enemy.current;
    enemy.current.x -= 1;
  } else {
    enemy.direction = 'R';
  }
}

// conditions for MEnemy to move left
bool MEnemy::can_move_left(SingleEnemy& enemy) {
  const char ch_1 =
      this->get_character({enemy.current.x - 1, enemy.current.y + 1});
  const char ch_2 = this->get_character({enemy.current.x - 1, enemy.current.y});

  return enemy.direction == 'L' && this->is_walkable(ch_1) && ch_2 != 'M' &&
         (ch_2 == ' ' || ch_2 == '&' || ch_2 == '*');
}

// MEnemy moves right
void MEnemy::move_right(SingleEnemy& enemy) {
  if (can_move_right(enemy)) {
    enemy.previous = enemy.current;
    enemy.current.x += 1;
  } else {
    enemy.direction = 'L';
  }
}

// conditions for MEnemy to move right
bool MEnemy::can_move_right(SingleEnemy& enemy) {
  const char ch_1 =
      this->get_character({enemy.current.x + 1, enemy.current.y + 1});
  const char ch_2 = this->get_character({enemy.current.x + 1, enemy.current.y});

  return enemy.direction == 'R' && this->is_walkable(ch_1) && ch_2 != 'M' &&
         (ch_2 == ' ' || ch_2 == '&' || ch_2 == '*');
}

bool MEnemy::is_enemy(const char ch) {
  return ch == Constants::Game::TENEMY_CHAR ||
         ch == Constants::Game::MENEMY_CHAR;
}

bool MEnemy::is_special(const char ch) {
  return ch == Constants::Game::LIFE_CHAR ||
         ch == Constants::Game::BONUS_CHAR ||
         ch == Constants::Game::SPAWN_CHAR || ch == Constants::Game::EXIT_CHAR;
}

// drawing updated MEnemy and resetting his previous position
void MEnemy::draw_updated() {
  for (std::size_t i = 0; i < this->enemies.size(); ++i) {
    this->print_character(this->enemies.at(i).previous, ' ');
    this->print_character(this->enemies.at(i).current, this->symbol);
  }
}

// removing MEnemy from the vector
void MEnemy::erase_enemy(int index) {
  this->enemies.erase(this->enemies.begin() + index);
}

void MEnemy::set_status(Status* status) {
  this->status = status;
}

}  // namespace Rush
