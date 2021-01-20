#include "Game.hpp"

namespace Rush {

Game::Game(const Levels &levels,
           const Player &player,
           int lives)
    : levels(levels),
      player(player),
      lives(lives),
      score(0),
      is_over(false) {}

void Game::run() {
  Map *map = &this->levels.get_curr().map;
  const Coordinate *spawn = &map->get_spawn();
  const Coordinate *exit = &map->get_exit();
  WINDOW *window = map->get_screen_window();

  map->draw();
  player.set_coordinate(*spawn);
  player.set_window(window);

  while (!is_over) {
    player.draw();
    player.move(getch());

    if (player.get_coordinate().x == spawn->x &&
        player.get_coordinate().y == spawn->y) {
      map = &this->levels.get_next().map;
      map->draw();
      spawn = &map->get_spawn();
      exit = &map->get_exit();

      player.set_coordinate(*spawn);
    }
  }
}

}  // namespace Rush
