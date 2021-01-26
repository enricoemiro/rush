#include "Game.hpp"

namespace Rush {

Game::Game() : lives(3), score(0), is_over(false) {
  this->player = new Player('&');
  this->levels =
      new Levels(Screen(Grid(40, 32), Coordinate(0, 0)), Grid(10, 8));
  this->status =
      new Status(Screen(Grid(8, 3), Coordinate(42, 0)),
                 this->levels->get_curr().value, this->score, this->lives);
}

Game::~Game() {
  delete this->player;
  delete this->levels;
  delete this->status;
}

void Game::run() {
  Level* level = &this->levels->get_curr();

  level->map.draw();
  this->status->draw();
  this->player->set_coordinate(level->map.get_spawn());
  this->player->set_window(level->map.get_screen_window());

  while (!this->is_over) {
    int key_pressed = getch();

    this->player->draw();
    this->player->move(key_pressed);
  }
}

}  // namespace Rush
