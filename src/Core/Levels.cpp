#include "Levels.hpp"

Level::Level()
    : value(1),
      map(nullptr),
      prev(nullptr),
      next(nullptr) {}

Levels::Levels(Screen *screen, Grid *grid)
    : screen(screen),
      grid(grid),
      head(nullptr) {
  this->insert_at_head();
}

Levels::~Levels() {
  if (this->head) {
    Level *curr = this->head;
    Level *next = nullptr;

    while (curr) {
      next = curr->next;
      if (curr->map) delete curr->map;
      delete curr;
      curr = next;
    }

    this->head = nullptr;
  }
}

void Levels::insert_at_head() {
  Level *new_level = new Level;
  new_level->map = new Map(this->screen, this->grid);
  new_level->prev = nullptr;

  if (!this->head) {
    new_level->value = 1;
  } else {
    new_level->value = this->head->value + 1;
    new_level->next = this->head;
    this->head->prev = new_level;
  }

  this->head = new_level;
}

Level *Levels::prev_level() {
  if (this->head->next != nullptr)
    this->head = this->head->next;

  return this->curr_level();
}

Level *Levels::curr_level() {
  return this->head;
}

Level *Levels::next_level() {
  if (this->head->prev == nullptr)
    this->insert_at_head();
  else
    this->head = this->head->prev;

  return this->curr_level();
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
