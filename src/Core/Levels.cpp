#include "Levels.hpp"

namespace Rush {

// Level struct
Levels::Level::Level(int value, const Screen& map_screen, const Grid& map_grid)
    : value(value),
      map(new Map(map_screen, map_grid)),
      t_enemies(new Enemy(this->map->get_screen_window(),
                          map_grid,
                          Constants::Game::TENEMY_CHAR)),
      m_enemies(new MEnemy(this->map->get_screen_window(),
                           map_grid,
                           Constants::Game::MENEMY_CHAR)),
      prev(nullptr),
      next(nullptr) {}

Levels::Level::~Level() {
  delete this->map;
  delete this->t_enemies;
  delete this->m_enemies;
}

// Levels class
Levels::Levels(const Screen& map_screen, const Grid& map_grid)
    : map_screen(map_screen), map_grid(map_grid), head(nullptr) {
  this->prepend();
}

Levels::~Levels() {
  if (this->head) {
    Level* curr = this->head;
    Level* next = nullptr;

    while (curr) {
      next = curr->next;
      curr->~Level();
      curr = next;
    }

    this->head = nullptr;
  }
}

void Levels::prepend() {
  Level* new_level = new Level(this->head ? this->head->value + 1 : 1,
                               this->map_screen, this->map_grid);

  if (this->head) {
    new_level->next = this->head;
    this->head->prev = new_level;
  }

  this->head = new_level;
}

void Levels::set_head_to_prev() {
  if (this->head->next != nullptr)
    this->head = this->head->next;
}

void Levels::set_head_to_next() {
  if (this->head->prev == nullptr)
    this->prepend();
  else
    this->head = this->head->prev;
}

int Levels::get_value() {
  return this->head->value;
}

Map* Levels::get_map() {
  return this->head->map;
}

Enemy* Levels::get_t_enemies() {
  return this->head->t_enemies;
}

MEnemy* Levels::get_m_enemies() {
  return this->head->m_enemies;
}

}  // namespace Rush
