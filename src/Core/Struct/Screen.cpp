#include "Screen.hpp"

namespace Rush {

Screen::Screen(const Grid &size,
               const Coordinate &start)
    : size(size),
      start(start),
      window(newwin(size.height + 2, size.width + 2, start.y, start.x)) {}

Screen::Screen(const Screen &other)
    : size(other.size),
      start(other.start),
      window(newwin(other.size.height + 2, other.size.width + 2, other.start.y, other.start.x)) {}

Screen::~Screen() {
  if (this->window) {
    delwin(this->window);
    this->window = nullptr;
  }
}

}  // namespace Rush
