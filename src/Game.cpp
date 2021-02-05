#include "Game.hpp"

namespace Rush {

Game::Game() {
  this->levels =
      new Levels(Screen(Grid(40, 32), Coordinate(0, 0)), Grid(10, 8));
  this->status = new Status(Screen(Grid(8, 3), Coordinate(42, 0)), 1, 0, 3);
  this->player = new Player(this->status, Constants::Game::PLAYER_CHAR);
  this->ui = new UI(Screen(Grid(40, 32), Coordinate(0, 0)));
}

Game::~Game() {
  delete this->levels;
  delete this->status;
  delete this->player;
  delete this->ui;
}

void Game::run() {
  this->ui->initial_screen();

  // Start the first level
  this->init_level();
  this->player->set_coordinate(this->levels->get_map()->get_spawn());

  // Run the game
  auto last = std::chrono::steady_clock::now();
  while (!this->status->get_is_over()) {
    this->draw_spawn();
    this->draw_exit();

    int key_pressed = getch();

    this->player->move(key_pressed);
    this->player->shoot(key_pressed);
    this->player->draw();

    // Go to the previous level
    // Qq = 81/113
    if (this->player->get_coordinate() ==
            this->levels->get_map()->get_spawn() &&
        (key_pressed == 81 || key_pressed == 113) &&
        this->levels->get_value() > 1)
      this->go_prev();

    // Go to the next level
    // Ee = 69/101
    if (this->player->get_coordinate() == this->levels->get_map()->get_exit() &&
        (key_pressed == 69 || key_pressed == 101))
      this->go_next();

    // Update bullets and m_enemies position
    std::chrono::duration<double> elapsed =
        std::chrono::steady_clock::now() - last;
    if (elapsed.count() >= 0.5f) {
      this->player->draw_bullets();
      this->levels->get_m_enemies()->update_enemies();
      last = std::chrono::steady_clock::now();
    }
  }

  this->ui->set_score(this->status->get_score());
  this->ui->game_over();
}

void Game::init_level() {
  int value = this->levels->get_value();
  Map* map = this->levels->get_map();
  Enemy* t_enemies = this->levels->get_t_enemies();
  MEnemy* m_enemies = this->levels->get_m_enemies();

  // Reset player bullets and coordinates
  this->player->reset_bullets();
  this->player->reset_coordinates();

  // Draw the map, update the status and the player
  map->draw();
  this->status->set_level(value);
  this->player->set_window(map->get_screen_window());

  // Set t_enemies
  t_enemies->set_level(value);
  t_enemies->set_rooms(map->get_rooms_vector());
  t_enemies->draw();

  // Set m_enemies
  m_enemies->set_level(value);
  m_enemies->set_rooms(map->get_rooms_vector());
  m_enemies->set_status(this->status);
  m_enemies->draw();
}

void Game::go_next() {
  this->levels->set_head_to_next();
  this->init_level();
  this->player->set_coordinate(this->levels->get_map()->get_spawn());
}

void Game::go_prev() {
  this->levels->set_head_to_prev();
  this->init_level();
  this->player->set_coordinate(this->levels->get_map()->get_exit());
}

void Game::draw_spawn() {
  const Coordinate& spawn_coordinate = this->levels->get_map()->get_spawn();
  const char spawn_ch = this->get_character(spawn_coordinate);

  if (spawn_ch != Constants::Game::SPAWN_CHAR && this->levels->get_value() > 1)
    this->add_character(spawn_coordinate, Constants::Game::SPAWN_CHAR);
}

void Game::draw_exit() {
  const Coordinate& exit_coordinate = this->levels->get_map()->get_exit();
  const char exit_ch = this->get_character(exit_coordinate);

  if (exit_ch != Constants::Game::EXIT_CHAR)
    this->add_character(exit_coordinate, Constants::Game::EXIT_CHAR);
}

char Game::get_character(const Coordinate& coordinate) {
  return mvwinch(this->levels->get_map()->get_screen_window(), coordinate.y,
                 coordinate.x);
}

void Game::add_character(const Coordinate& coordinate, const char ch) {
  mvwaddch(this->levels->get_map()->get_screen_window(), coordinate.y,
           coordinate.x, ch);
}

}  // namespace Rush
