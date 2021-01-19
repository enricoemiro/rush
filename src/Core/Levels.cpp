#include "Levels.hpp"

namespace Rush {

Levels::Levels(const Levels &other)
    : map_screen(other.map_screen),
      map_grid(other.map_grid),
      head(other.head) {}

Levels::Levels(const Screen &map_screen,
               const Grid &map_grid)
    : map_screen(map_screen),
      map_grid(map_grid),
      head(nullptr) {
  this->prepend();
}

Levels::~Levels() {
  if (this->head) {
    Level *curr = this->head;
    Level *next = nullptr;

    while (curr) {
      next = curr->next;
      delete curr;
      curr = next;
    }

    this->head = nullptr;
  }
}

void Levels::prepend() {
  Level *new_level = new Level(
      this->head ? this->head->value + 1 : 1,
      this->map_screen,
      this->map_grid);

  if (this->head) {
    new_level->next = this->head;
    this->head->prev = new_level;
  }

  this->head = new_level;
}

Level &Levels::get_prev() {
  if (this->head->next)
    this->head = this->head->next;

  return this->get_curr();
}

Level &Levels::get_curr() {
  return *this->head;
}

Level &Levels::get_next() {
  if (!this->head->prev)
    this->prepend();
  else
    this->head = this->head->prev;

  return this->get_curr();
}

#if DEBUG == 1
void Levels::print() {
  Level *tmp = this->head;

  while (tmp) {
    std::cout << tmp->value << " => ";

    if (tmp->prev)
      std::cout << "Next: " << tmp->prev->value << " ";

    if (tmp->next)
      std::cout << "Prev: " << tmp->next->value << " ";

    std::cout << std::endl;
    tmp = tmp->next;
  }
}
#endif

}  // namespace Rush
