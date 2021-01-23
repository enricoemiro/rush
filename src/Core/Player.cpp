#include "Player.hpp"

namespace Rush {

Player::Player(char symbol)
    : map_window(nullptr),
      symbol(symbol),
      current(Coordinate(-1, -1)),
      previous(Coordinate(-1, -1)) {}

void Player::jump(const Coordinate& next, bool& has_jumped) {
  const char ch_1 = mvwinch(map_window, next.y, this->current.x) & A_CHARTEXT;

  const char ch_2 =
      mvwinch(map_window, next.y - 1, this->current.x) & A_CHARTEXT;

  if (ch_1 == '=' || ch_1 == 'X')
    has_jumped = true;
  if (ch_1 == '=' && ch_2 == ' ')
    this->current.y = next.y - 1;
}

void Player::jump_up() {
  bool has_jumped = false;

  for (int i = this->current.y - 1; i > 1 && !has_jumped; --i)
    this->jump(Coordinate(this->current.x, i), has_jumped);
}

void Player::jump_down() {
  bool has_jumped = false;

  for (int i = this->current.y + 2;
       i < getmaxy(this->map_window) - 1 && !has_jumped; ++i)
    this->jump(Coordinate(this->current.x, i), has_jumped);
}

void Player::move(int key_pressed) {
  if (key_pressed != KEY_RIGHT && key_pressed != KEY_LEFT &&
      key_pressed != KEY_UP && key_pressed != KEY_DOWN)
    return;

  // Save previous position
  this->previous = this->current;

  if (key_pressed == KEY_UP)
    this->jump_up();

  if (key_pressed == KEY_DOWN)
    this->jump_down();

  if (key_pressed == KEY_RIGHT || key_pressed == KEY_LEFT) {
    this->current.x += key_pressed == KEY_RIGHT ? 1 : -1;

    const char ch_1 =
        mvwinch(this->map_window, this->current.y - 1, this->current.x) &
        A_CHARTEXT;
    const char ch_2 =
        mvwinch(this->map_window, this->current.y, this->current.x) &
        A_CHARTEXT;
    const char ch_3 =
        mvwinch(this->map_window, this->previous.y - 1, this->previous.x) &
        A_CHARTEXT;

    // If the player encounters a single block, jump on it
    //           &
    //  &=   ->  =
    // ====    ====
    if (ch_1 == ' ' && ch_2 == '=' && ch_3 != '=')
      this->current.y -= 1;

    // If the player encounters:
    // - right edge
    // - left edge
    // - double block
    // - wall
    // stops it
    if (this->current.x >= getmaxx(map_window) - 1 ||
        this->current.x <= getbegx(map_window) ||
        (ch_1 == '=' && ch_2 == '=') || ch_2 == 'X')
      this->current = this->previous;

    // If the player is flying, its jump down
    //  &
    //  =   ->  =&
    // ====    ====
    if (static_cast<const char>(
            mvwinch(this->map_window, this->current.y + 1, this->current.x) &
            A_CHARTEXT) != '=')
      this->jump_down();
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
