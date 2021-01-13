#include "Screen.hpp"

Screen::Screen(int width,
               int height,
               int start_x,
               int start_y)
    : width(width),
      height(height),
      start_x(start_x),
      start_y(start_y),
      window(newwin(height + 2, width + 2, start_y, start_x)) {}

Screen::~Screen() {
  if (this->window) {
    delwin(this->window);
    this->window = nullptr;
  }
}
