#include "Game.hpp"

namespace Rush {

Game::Game() {
  this->levels =
      new Levels(Screen(Grid(40, 32), Coordinate(0, 0)), Grid(10, 8));
  this->status = new Status(Screen(Grid(8, 3), Coordinate(42, 0)), 1, 0, 3);
  this->player = new Player(this->status, '&');
}

Game::~Game() {
  delete this->levels;
  delete this->status;
  delete this->player;
}

void Game::run() {
  Level_Ptr level = this->levels->get_curr();

  // Start the first level
  this->init_level(level);
  this->player->set_coordinate(level->map->get_spawn());

  // Run the game
  auto last = time(0);
  while (!this->status->get_is_over()) {
    int key_pressed = getch();

    this->player->move(key_pressed);
    this->player->shoot(key_pressed);

    // Go to the previous level
    // Qq = 81/113
    if (this->player->get_coordinate() == level->map->get_spawn() &&
        (key_pressed == 81 || key_pressed == 113) && level->value > 1)
      this->go_prev(level);

    // Go to the next level
    // Ee = 69/101
    if (this->player->get_coordinate() == level->map->get_exit() &&
        (key_pressed == 69 || key_pressed == 101))
      this->go_next(level);

    if (time(0) - last >= 1) {
      this->player->draw_bullets();
      level->m_enemies->update_enemies();
      last = time(0);
    }

    this->player->draw();
    this->draw_spawn_exit_point(level);
  }
}

void Game::init_level(Level_Ptr& level) {
  this->player->reset_bullets();
  this->player->reset_coordinates();
  level->map->draw();
  this->status->set_level(level->value);
  this->player->set_window(level->map->get_screen_window());

  // Set the enemies
  level->t_enemies->set_level(level->value);
  level->t_enemies->set_rooms(level->map->get_rooms_vector());
  level->t_enemies->draw();

  level->m_enemies->set_level(level->value);
  level->m_enemies->set_rooms(level->map->get_rooms_vector());
  level->m_enemies->draw();
}

void Game::go_next(Level_Ptr& level) {
  level = this->levels->get_next();
  this->init_level(level);
  this->player->set_coordinate(level->map->get_spawn());
}

void Game::go_prev(Level_Ptr& level) {
  level = this->levels->get_prev();
  this->init_level(level);
  this->player->set_coordinate(level->map->get_exit());
}

void Game::draw_spawn(Level_Ptr& level) {
  const char spawn_ch = this->get_character(level, level->map->get_spawn());

  if (spawn_ch != 'S' && level->value != 1)
    this->add_character(level, level->map->get_spawn(), 'S');
}

void Game::draw_exit(Level_Ptr& level) {
  const char exit_ch = this->get_character(level, level->map->get_spawn());

  if (exit_ch != 'E')
    this->add_character(level, level->map->get_exit(), 'E');
}

void Game::draw_spawn_exit_point(Level_Ptr& level) {
  this->draw_spawn(level);
  this->draw_exit(level);
}

char Game::get_character(Level_Ptr& level, const Coordinate& coordinate) {
  return mvwinch(level->map->get_screen_window(), coordinate.y, coordinate.x);
}

void Game::add_character(Level_Ptr& level,
                         const Coordinate& coordinate,
                         const char ch) {
  mvwaddch(level->map->get_screen_window(), coordinate.y, coordinate.x, ch);
}

}  // namespace Rush
