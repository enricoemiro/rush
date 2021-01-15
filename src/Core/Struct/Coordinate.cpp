#include "Coordinate.hpp"

namespace Rush {

Coordinate::Coordinate(int x,
                       int y)
    : x(x),
      y(y) {}

Coordinate::Coordinate(const Coordinate &other)
    : x(other.x),
      y(other.y) {}

}  // namespace Rush
