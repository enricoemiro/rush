#include "Enemy.hpp"

namespace Rush {

Enemy::Enemy(WINDOW* map_window, const Grid& grid, char symbol)
    : map_window(map_window), grid(grid), symbol(symbol) {
  this->level = 1;
  this->was_drawn = false;
}

Enemy::~Enemy() {}

void Enemy::draw() {
  if (!this->was_drawn) {
    for (std::size_t i = 1; i < this->rooms.size(); ++i)
      this->select_y(i);
    this->was_drawn = true;
  }
}

void Enemy::select_y(int room_index) {
  for (int i = this->rooms.at(room_index).start.y;
       i < this->rooms.at(room_index).start.y + this->grid.height; ++i)
    this->select_x(room_index, i);
}

void Enemy::select_x(int room_index, int y_index) {
  for (int i = this->rooms.at(room_index).start.x;
       i < this->rooms.at(room_index).start.x + this->grid.width; ++i)
    this->spawn_conditions(Coordinate(i, y_index));
}

char Enemy::get_character(const Coordinate& coordinate) {
  return mvwinch(this->map_window, coordinate.y, coordinate.x) & A_CHARTEXT;
}

void Enemy::spawn_conditions(const Coordinate& coordinate) {
  const char ch_1 = this->get_character(coordinate);
  const char ch_2 = this->get_character({coordinate.x, coordinate.y + 1});

  if (this->is_space(ch_1) && this->is_walkable(ch_2) &&
      rand() % 100 <= level * 2)
    this->print_character(coordinate, this->symbol);
}

bool Enemy::is_space(const char ch) {
  return ch == Constants::Game::SPACE_CHAR;
}

bool Enemy::is_walkable(const char ch) {
  return ch == Constants::Game::FLOOR_CHAR || ch == Constants::Game::BLOCK_CHAR;
}

void Enemy::set_rooms(const std::vector<Room>& rooms) {
  this->rooms = rooms;
}

void Enemy::set_level(int level) {
  this->level = level;
}

void Enemy::print_character(const Coordinate& coordinate, const char ch) {
  mvwaddch(this->map_window, coordinate.y, coordinate.x, ch);
}

}  // namespace Rush
