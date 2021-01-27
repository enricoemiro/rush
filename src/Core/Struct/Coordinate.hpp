#ifndef COORDINATE_HPP
#define COORDINATE_HPP

namespace Rush {

struct Coordinate {
  int x, y;

  Coordinate(int x, int y);
  Coordinate(const Coordinate& other);
  Coordinate& operator=(const Coordinate& other);
  bool operator==(const Coordinate& other) const;
};

}  // namespace Rush

#endif
