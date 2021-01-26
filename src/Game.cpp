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
  Level* level = &this->levels->get_curr();

  level->map.draw();
  this->status->draw();
  this->player->set_coordinate(level->map.get_spawn());
  this->player->set_window(level->map.get_screen_window());

  while (!this->status->get_is_over()) {
    int key_pressed = getch();

    this->player->draw();
    this->player->move(key_pressed);
  }
}

}  // namespace Rush
