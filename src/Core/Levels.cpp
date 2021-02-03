#include "Levels.hpp"

namespace Rush {

Levels::Levels(const Levels& other)
    : map_screen(other.map_screen),
      map_grid(other.map_grid),
      head(other.head) {}

Levels::Levels(const Screen& map_screen, const Grid& map_grid)
    : map_screen(map_screen), map_grid(map_grid), head(nullptr) {
  this->prepend();
}

Levels::~Levels() {
  if (this->head) {
    Level_Ptr curr = this->head;
    Level_Ptr next = nullptr;

    while (curr) {
      next = curr->next;
      curr->~Level();
      curr = next;
    }

    this->head = nullptr;
  }
}

void Levels::prepend() {
  Level_Ptr new_level = new Level(this->head ? this->head->value + 1 : 1,
                                  this->map_screen, this->map_grid);

  if (this->head) {
    new_level->next = this->head;
    this->head->prev = new_level;
  }

  this->head = new_level;
}

Level_Ptr Levels::get_prev() {
  if (this->head->next != nullptr)
    this->head = this->head->next;

  return this->get_curr();
}

Level_Ptr Levels::get_curr() {
  return this->head;
}

Level_Ptr Levels::get_next() {
  if (this->head->prev == nullptr)
    this->prepend();
  else
    this->head = this->head->prev;

  return this->get_curr();
}

}  // namespace Rush
