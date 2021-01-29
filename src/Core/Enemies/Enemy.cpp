#include "Enemy.hpp"

namespace Rush {

Enemy::Enemy(WINDOW* map_window, const Grid& grid, char symbol)
    : map_window(map_window), grid(grid), symbol(symbol) {
  this->level = 1;
  this->was_drawn = false;
}

void Enemy::draw() {
  if (!this->was_drawn) {
    for (std::size_t i = 0; i < this->rooms.size(); ++i)
      this->select_y(i);
    this->was_drawn = true;
  }
}

void Enemy::select_y(int room_index) {
  for (int i = this->rooms.at(room_index).start.y + 1;
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
  if (this->get_character(Coordinate(coordinate.x, coordinate.y + 1)) == '=' &&
      (this->get_character(coordinate) == ' ') && (rand() % 100 <= level * 3))
    this->print_character(coordinate, this->symbol);
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
