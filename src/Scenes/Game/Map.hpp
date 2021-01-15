#ifndef MAP_HPP
#define MAP_HPP

#include <ncurses.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../Core/Struct/Coordinate.hpp"
#include "../../Core/Struct/Grid.hpp"
#include "../../Core/Struct/Room.hpp"
#include "../../Utilities/Constants.hpp"
#include "../../Utilities/Macros.hpp"
#include "../Scene.hpp"

namespace Rush {

class Map : public Scene {
  static const char CORRIDOR_ROOM_CODE = '1';
  static const char DROP_ROOM_CODE = '2';
  static const char LANDING_ROOM_CODE = '3';
  static const char OPEN_ROOM_CODE = '4';
  static const char SPAWN_ROOM_CODE = 'S';
  static const char EXIT_ROOM_CODE = 'E';

 private:
  Grid grid;
  std::vector<Room> rooms;
  std::vector<Coordinate> spawn_exit;
  int number_rows;
  int number_columns;

  void generate_solution_path();
  std::string *get_available_moves(const Room &last_room);
  const bool can_move(const Coordinate &coordinate);
  void replace_solution_path();
  void add_room(const Coordinate &start,
                const std::vector<std::string> *rooms);

 public:
  Map(const Screen &screen,
      const Grid &grid);
  void draw();
  const Coordinate &get_spawn();
  const Coordinate &get_exit();
};

}  // namespace Rush

#endif
