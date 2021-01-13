#ifndef MAP_HPP
#define MAP_HPP

#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../Constants.hpp"
#include "../../Core/Struct/Grid.hpp"
#include "../Scene.hpp"

#define EXIT_IF_TRUE(expression, msg) \
  {                                   \
    if (expression) {                 \
      endwin();                       \
      std::cout << msg << std::endl;  \
      exit(EXIT_FAILURE);             \
    }                                 \
  }

struct Room {
  char type;
  int start_x;
  int start_y;

  Room(char type, int start_x, int start_y);
  Room(const Room &room);
};

class Map : public Scene {
  // It as a left and right exit
  static const char CORRIDOR_ROOM_CODE = '1';

  // It has a left, right and bottom exit
  static const char DROP_ROOM_CODE = '2';

  // It has a left, right and top exit
  static const char LANDING_ROOM_CODE = '3';

  // It has an exit on all four sides
  static const char OPEN_ROOM_CODE = '4';

 private:
  Grid *grid;
  std::vector<Room> rooms;
  int grids_per_width;
  int grids_per_height;

  void generate_solution_path();
  std::string *get_available_moves(Room *next_room);
  const bool can_move(int x, int y);
  void replace_solution_path();
  void add_room(int x, int y, const std::vector<std::string> *rooms);

 public:
  Map(Screen *screen, Grid *grid);
  void draw();
};

#endif
