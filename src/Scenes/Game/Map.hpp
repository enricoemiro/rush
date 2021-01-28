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
  static const char CORRIDOR_ROOM_CODE;
  static const char DROP_ROOM_CODE;
  static const char LANDING_ROOM_CODE;
  static const char OPEN_ROOM_CODE;
  static const char SPAWN_CORRIDOR_ROOM_CODE;
  static const char SPAWN_DROP_ROOM_CODE;
  static const char EXIT_CORRIDOR_ROOM_CODE;
  static const char EXIT_LANDING_ROOM_CODE;

 private:
  Grid grid;
  std::vector<Room> rooms;
  std::vector<Coordinate> spawn_exit;
  int number_rows;
  int number_columns;
	bool was_drawn;

  void generate_solution_path();
  void replace_solution_path();
  void add_room(const Coordinate& start, const std::vector<std::string>* rooms);

  /** Helpers */
  void print_room(const Room& room);
  char get_character(const Coordinate& coordinate);

  bool can_move(const Coordinate& coordinate);
  std::string get_available_moves(const Room& room);
  char get_move(const Room& room);
  void move(Room& last_room, Room& room, char move_ch);
  void move_right(Room& room);
  void move_left(Room& room);
  void move_down(Room& last_room, Room& room);
  void update_spawn_type();
  void update_exit_type();

  void add_rooms(int row);
  const std::vector<std::string>* get_room_templates(char room_type);
  const std::string* get_room_template(const std::vector<std::string>* rooms);
  /***********/

 public:
  Map(const Screen& screen, const Grid& grid);
  void draw();

  // Getters
  const Coordinate& get_spawn() const;
  const Coordinate& get_exit() const;
  const std::vector<Room>& get_rooms_vector() const;
  const Grid& get_grid() const;
};

}  // namespace Rush

#endif
