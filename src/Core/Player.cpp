#include "Player.hpp"

namespace Rush {

// Bullet struct
Player::Bullet::Bullet(char direction, const Coordinate& current)
    : direction(direction), current(current), previous({-1, -1}) {}

Player::Player(Status* status, char symbol)
    : status(status),
      symbol(symbol),
      map_window(nullptr),
      current({-1, -1}),
      previous({-1, -1}),
      has_moved(true) {
  this->bullets.reserve(4);
}

char Player::get_character(const Coordinate& coordinate) {
  return mvwinch(this->map_window, coordinate.y, coordinate.x) & A_CHARTEXT;
}

void Player::clear(const Coordinate& coordinate) {
  mvwaddch(this->map_window, coordinate.y, coordinate.x, ' ');
}

void Player::jump(const Coordinate& coordinate, bool& has_jumped) {
  const char ch_1 = this->get_character(coordinate);
  const char ch_2 = this->get_character({coordinate.x, coordinate.y - 1});

  if (this->is_block(ch_1) || this->is_floor(ch_1) || this->is_wall(ch_1)) {
    has_jumped = true;

    if (!this->is_block(ch_2) && !this->is_wall(ch_2) &&
        !this->is_floor(ch_2)) {
      this->current.y = coordinate.y - 1;
      this->collision(this->current);
    }
  }
}

void Player::jump_up() {
  bool has_jumped = false;

  for (int i = this->current.y - 1;
       i > 1 && !has_jumped &&
       !is_floor(this->get_character({this->current.x, i}));
       --i)
    this->jump({this->current.x, i}, has_jumped);
}

void Player::jump_down() {
  bool has_jumped = false;

  // The player can't jump down if he's already on the floor
  if (this->is_floor(
          this->get_character({this->current.x, this->current.y + 1})))
    return;

  for (int i = this->current.y + 2;
       i < getmaxy(this->map_window) - 1 && !has_jumped; ++i)
    this->jump({this->current.x, i}, has_jumped);
}

void Player::collision(const Coordinate& coordinate) {
  const char hitted_char = this->get_character(coordinate);

  if (hitted_char == Constants::Game::BONUS_CHAR) {
    this->status->increment_score(10);
    this->clear(coordinate);
  }

  if (hitted_char == Constants::Game::LIFE_CHAR) {
    this->status->increment_lives();
    this->clear(coordinate);
  }

  if (this->is_enemy(hitted_char)) {
    this->status->decrement_lives();
    this->clear(coordinate);
  }
}

bool Player::is_right_edge(const Coordinate& coordinate) {
  return coordinate.x >= getmaxx(this->map_window) - 1;
}

bool Player::is_left_edge(const Coordinate& coordinate) {
  return coordinate.x <= getbegx(this->map_window);
}

bool Player::is_double_block(const Coordinate& coordinate) {
  return this->is_block(this->get_character(coordinate)) &&
         (this->is_block(
              this->get_character({coordinate.x, coordinate.y - 1})) ||
          coordinate.y - 1 == 0);
}

bool Player::is_enemy(const char ch) {
  return ch == Constants::Game::MENEMY_CHAR ||
         ch == Constants::Game::TENEMY_CHAR;
}

bool Player::is_block(const char ch) {
  return ch == Constants::Game::BLOCK_CHAR;
}

bool Player::is_floor(const char ch) {
  return ch == Constants::Game::FLOOR_CHAR;
}

bool Player::is_wall(const char ch) {
  return ch == Constants::Game::WALL_CHAR;
}

bool Player::is_flying(const char ch) {
  return !this->is_floor(ch) && !this->is_block(ch);
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

    const char ch_1 = this->get_character(this->current);
    const char ch_2 =
        this->get_character({this->previous.x, this->previous.y - 1});

    // Stops the player
    if (is_right_edge(this->current) || is_left_edge(this->current) ||
        is_double_block(this->current) || is_wall(ch_1) ||
        (is_block(ch_2) && is_block(ch_1)))
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
    if (this->is_flying(
            this->get_character({this->current.x, this->current.y + 1})))
      this->jump_down();

    // Check for collision
    this->collision(this->current);
  }

  this->has_moved = true;
}

void Player::shoot(int key_pressed) {
  // Keys:
  // Ww = 87/119
  // Aa = 65/97
  // Ss = 83/115
  // Dd = 68/100
  if ((key_pressed != 87 && key_pressed != 119 && key_pressed != 65 &&
       key_pressed != 97 && key_pressed != 83 && key_pressed != 115 &&
       key_pressed != 68 && key_pressed != 100) ||
      this->bullets.size() >= 4)
    return;

  char direction;

  // clang-format off
  if (key_pressed == 87 || key_pressed == 119) direction = 'W';
  if (key_pressed == 65 || key_pressed == 97) direction = 'A';
  if (key_pressed == 83 || key_pressed == 115) direction = 'S';
  if (key_pressed == 68 || key_pressed == 100) direction = 'D';
  // clang-format on

  this->bullets.emplace_back(direction, this->current);
}

void Player::shoot_up(Coordinate& coordinate) {
  if (this->is_block(this->get_character(coordinate)) &&
      !this->is_double_block(coordinate))
    coordinate.y -= 1;
}

void Player::shoot_down(Coordinate& coordinate) {
  if (this->is_block(this->get_character(coordinate)) &&
      !this->is_double_block(coordinate))
    coordinate.y += 1;
}

void Player::update_bullets() {
  for (size_t i = 0; i < this->bullets.size(); ++i) {
    auto bullet = &this->bullets.at(i);

    // Save previous position
    bullet->previous = bullet->current;

    if (bullet->direction == 'W') {
      bullet->current.y -= 1;
      this->shoot_up(bullet->current);
    }

    if (bullet->direction == 'S') {
      bullet->current.y += 1;
      this->shoot_down(bullet->current);
    }

    // clang-format off
    if (bullet->direction == 'A') bullet->current.x -= 1;
    if (bullet->direction == 'D') bullet->current.x += 1;
    // clang-format on

    // Check for collision
    const char hitted_char = this->get_character(bullet->current);

    if (hitted_char != ' ') {
      if (this->is_enemy(hitted_char)) {
        this->status->increment_score(20);
        this->clear(bullet->current);
      }

      if (this->symbol == hitted_char) {
        this->status->decrement_lives();
        this->clear(bullet->current);
      }

      this->clear(bullet->previous);
      this->bullets.erase(this->bullets.begin() + i);
    }
  }
}

void Player::draw_bullets() {
  this->update_bullets();

  for (auto const& bullet : this->bullets) {
    mvwaddch(this->map_window, bullet.previous.y, bullet.previous.x, ' ');
    mvwaddch(this->map_window, bullet.current.y, bullet.current.x, '*');
    wrefresh(this->map_window);
  }
}

void Player::draw() {
  if (this->has_moved) {
    mvwaddch(this->map_window, this->previous.y, this->previous.x, ' ');
    this->has_moved = false;
  }
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

void Player::reset_coordinates() {
  this->current = {-1, -1};
  this->previous = {-1, -1};
}

void Player::reset_bullets() {
  for (auto const& bullet : this->bullets)
    mvwaddch(this->map_window, bullet.current.y, bullet.current.x, ' ');

  this->bullets.clear();
}

}  // namespace Rush
