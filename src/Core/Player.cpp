#include "Player.hpp"

namespace Rush {

Player::Player(Status* status, char symbol)
    : status(status),
      symbol(symbol),
      map_window(nullptr),
      current({-1, -1}),
      previous({-1, -1}) {}

char Player::get_character(const Coordinate& coordinate) {
  return mvwinch(this->map_window, coordinate.y, coordinate.x) & A_CHARTEXT;
}

void Player::jump(const Coordinate& coordinate, bool& has_jumped) {
  if (this->is_block(coordinate) || this->is_wall(coordinate))
    has_jumped = true;

  if (this->is_block(coordinate) &&
      !this->is_block({coordinate.x, coordinate.y - 1})) {
    this->current.y = coordinate.y - 1;
    this->collision(this->current);
  }
}

void Player::jump_up() {
  bool has_jumped = false;

  for (int i = this->current.y - 1; i > 1 && !has_jumped; --i)
    this->jump({this->current.x, i}, has_jumped);
}

void Player::jump_down() {
  bool has_jumped = false;

  for (int i = this->current.y + 2;
       i < getmaxy(this->map_window) - 1 && !has_jumped; ++i)
    this->jump({this->current.x, i}, has_jumped);
}

void Player::collision(const Coordinate& coordinate) {
  const char hitted_char = this->get_character(coordinate);

  // clang-format off
	if (hitted_char == 'B') this->status->increment_score(10);
  if (hitted_char == 'L') this->status->increment_lives();
	if (hitted_char == 'M' || hitted_char == 'T') this->status->decrement_lives();
  // clang-format on
}

bool Player::is_flying(const Coordinate& coordinate) {
  return this->get_character({coordinate.x, coordinate.y + 1}) != '=';
}

bool Player::is_right_edge(const Coordinate& coordinate) {
  return coordinate.x >= getmaxx(this->map_window) - 1;
}

bool Player::is_left_edge(const Coordinate& coordinate) {
  return coordinate.x <= getbegx(this->map_window);
}

bool Player::is_block(const Coordinate& coordinate) {
  return this->get_character(coordinate) == '=';
}

bool Player::is_double_block(const Coordinate& coordinate) {
  return this->get_character(coordinate) == '=' &&
         (this->get_character({coordinate.x, coordinate.y - 1}) == '=' ||
          coordinate.y - 1 == 0);
}

bool Player::is_wall(const Coordinate& coordinate) {
  return this->get_character(coordinate) == 'X';
}

void Player::move(int key_pressed) {
  if (key_pressed != KEY_RIGHT && key_pressed != KEY_LEFT &&
      key_pressed != KEY_UP && key_pressed != KEY_DOWN)
    return;

  // Save previous position
  this->previous = this->current;

  // clang-format off
  if (key_pressed == KEY_UP) this->jump_up();
  if (key_pressed == KEY_DOWN) this->jump_down();
  // clang-format on

  if (key_pressed == KEY_RIGHT || key_pressed == KEY_LEFT) {
    this->current.x += key_pressed == KEY_RIGHT ? 1 : -1;

    // Stops the player
    if (is_right_edge(this->current) || is_left_edge(this->current) ||
        is_double_block(this->current) || is_wall(this->current) ||
        (is_block({this->previous.x, this->previous.y - 1}) &&
         is_block(this->current)))
      this->current = this->previous;

    // If the player encounters a single block, jump on it
    //           &
    //  &=   ->  =
    // ====    ====
    if (!is_double_block(this->current))
      this->current.y -= 1;

    // If the player is flying, its jump down
    //  &
    //  =   ->  =&
    // ====    ====
    if (is_flying(this->current))
      this->jump_down();

    // Check for collision
    this->collision(this->current);
  }
}

void Player::draw() {
  mvwaddch(this->map_window, this->previous.y, this->previous.x, ' ');
  mvwaddch(this->map_window, this->current.y, this->current.x, this->symbol);
  wmove(this->map_window, this->current.y, this->current.x);
  wrefresh(this->map_window);
}

const Coordinate& Player::get_coordinate() {
  return this->current;
}

void Player::set_coordinate(const Coordinate& coordinate) {
  this->current = coordinate;
}

void Player::set_window(WINDOW* map_window) {
  this->map_window = map_window;
}

}  // namespace Rush
