#include "Coordinate.hpp"

namespace Rush {

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

Coordinate::Coordinate(const Coordinate& other) : x(other.x), y(other.y) {}

Coordinate& Coordinate::operator=(const Coordinate& other) {
  this->x = other.x;
  this->y = other.y;
  return *this;
}

bool Coordinate::operator==(const Coordinate& other) const {
  return this->x == other.x && this->y == other.y;
}

}  // namespace Rush
