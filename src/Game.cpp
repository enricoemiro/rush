#include "Game.hpp"

namespace Rush {

Game::Game() : lives(3), score(0), is_over(false) {
  this->player = new Player('&');
  this->levels =
      new Levels(Screen(Grid(40, 32), Coordinate(0, 0)), Grid(10, 8));
}

Game::~Game() {
  delete this->player;
  delete this->levels;
}

void Game::run() {
  Level* level = &this->levels->get_curr();

  level->map.draw();
  this->player->set_coordinate(level->map.get_spawn());
  this->player->set_window(level->map.get_screen_window());

  while (!this->is_over) {
    this->player->draw();
    this->player->move(getch());
  }
}

}  // namespace Rush
