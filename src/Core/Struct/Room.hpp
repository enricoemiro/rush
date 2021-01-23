#ifndef ROOM_HPP
#define ROOM_HPP

#include "Coordinate.hpp"

namespace Rush {

struct Room {
  char type;
  Coordinate start;

  Room(char type, const Coordinate& start);
};

}  // namespace Rush

#endif
