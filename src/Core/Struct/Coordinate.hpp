#ifndef COORDINATE_HPP
#define COORDINATE_HPP

namespace Rush {

struct Coordinate {
  int x, y;

  Coordinate(int x, int y);
  Coordinate(const Coordinate& other);
};

}  // namespace Rush

#endif
