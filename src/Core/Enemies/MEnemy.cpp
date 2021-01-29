#include "MEnemy.hpp"

namespace Rush {

MEnemy::MEnemy(WINDOW* map_window, const Grid& grid, char symbol)
    : Enemy(map_window, grid, symbol) {
  this->status = nullptr;
}

void MEnemy::update_enemies() {
  this->update_positions();
  this->draw_updated();
  wrefresh(map_window);
}

void MEnemy::spawn_conditions(const Coordinate& coordinate) {
  if (this->get_character(Coordinate(coordinate.x, coordinate.y + 1)) == '=' &&
      (this->get_character(coordinate) == ' ') && (rand() % 100 <= level * 2)) {
    this->print_character(coordinate, this->symbol);
    this->enemies.push_back({'R', coordinate, coordinate});
  }
}

void MEnemy::update_positions() {
  for (std::size_t i = 0; i < this->enemies.size(); ++i) {
    this->move_right(this->enemies.at(i));
    this->move_left(this->enemies.at(i));
  }
}

void MEnemy::move_left(SingleEnemy& enemy) {
  if (can_move_left(enemy)) {
    enemy.previous = enemy.current;
    enemy.current.x -= 1;
  } else {
    enemy.direction = 'R';
  }
}

bool MEnemy::can_move_left(SingleEnemy& enemy) {
  return enemy.direction == 'L' &&
         this->get_character(
             Coordinate(enemy.current.x - 1, enemy.current.y + 1)) == '=' &&
         this->get_character(
             Coordinate(enemy.current.x - 1, enemy.current.y)) == ' ';
}

void MEnemy::move_right(SingleEnemy& enemy) {
  if (can_move_right(enemy)) {
    enemy.previous = enemy.current;
    enemy.current.x += 1;
  } else {
    enemy.direction = 'L';
  }
}

bool MEnemy::can_move_right(SingleEnemy& enemy) {
  return enemy.direction == 'R' &&
         this->get_character(
             Coordinate(enemy.current.x + 1, enemy.current.y + 1)) == '=' &&
         this->get_character(
             Coordinate(enemy.current.x + 1, enemy.current.y)) == ' ';
}

void MEnemy::draw_updated() {
  for (std::size_t i = 0; i < this->enemies.size(); ++i) {
    this->print_character(this->enemies.at(i).previous, ' ');
    this->print_character(this->enemies.at(i).current, this->symbol);
  }
}

void MEnemy::set_status(Status* status) {
  this->status = status;
}

}  // namespace Rush
