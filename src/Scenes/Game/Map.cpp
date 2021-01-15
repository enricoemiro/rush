#include "Map.hpp"

namespace Rush {

Map::Map(const Screen &screen, const Grid &grid)
    : Scene(screen),
      grid(grid) {
  EXIT_IF_TRUE(this->screen.size.width < grid.width ||
                   this->screen.size.height < grid.height,
               "The screen must have a minimum size of "
                   << grid.width << "x" << grid.height);

  EXIT_IF_TRUE(this->screen.size.width % grid.width != 0,
               "The width of the screen must be divisible by" << grid.width);

  EXIT_IF_TRUE(this->screen.size.width % grid.height != 0,
               "The height of the screen must be divisible by " << grid.height)

  this->number_columns = this->screen.size.width / this->grid.width;
  this->number_rows = this->screen.size.height / this->grid.height;

  // Memory reserve for vectors.
  // (Doing so the vector doesn't have to be copied
  // every time a new element must be added)
  this->rooms.reserve(this->number_columns * this->number_rows);
  this->spawn_exit.reserve(2);
}

void Map::draw() {
  this->draw_edges();
  this->generate_solution_path();
  this->replace_solution_path();
  this->refresh();
}

void Map::generate_solution_path() {
  // Place the spawn room in the top row
  this->rooms.push_back({CORRIDOR_ROOM_CODE,
                         Coordinate(
                             rand() % this->number_columns * this->grid.width + 1,
                             1)});

  // Print the spawn type room to the screen
  mvwaddch(this->screen.window,
           this->rooms.front().start.y,
           this->rooms.front().start.x,
           this->rooms.front().type);

  // Keeps track of the last room placed
  // (at the beginning it points to the spawn room)
  Room *last_room = &this->rooms.front();

  while (true) {
    // Make a copy of the last room placed
    Room next_room(CORRIDOR_ROOM_CODE, Coordinate(last_room->start));

    const std::string *moves = get_available_moves(next_room);
    const int move_idx = rand() % moves->size();
    const char move_ch = moves->at(move_idx);
    delete moves;

    // The solution path moves right
    if (move_ch == 'R')
      next_room.start.x += this->grid.width;

    // The solution path moves left
    if (move_ch == 'L')
      next_room.start.x -= this->grid.width;

    // The solution path moves down
    if (move_ch == 'D') {
      next_room.start.y += this->grid.height;

      // If the new ordinate exceed the screen height,
      // draw the exit and stop the generation
      if (next_room.start.y >= this->screen.size.height) break;

      // Update the last room to be type 2 and print it to the screen
      this->rooms.back().type = DROP_ROOM_CODE;
      mvwaddch(this->screen.window, last_room->start.y, last_room->start.x, last_room->type);

      // The next room MUST be type 3
      next_room.type = LANDING_ROOM_CODE;
    }

    // 0) If the previous two rooms were type 2,
    // replace the last room type to be type 4
    if (this->rooms.size() > 3) {
      // Points to the third last room created
      Room *third_last_room = *(&last_room - sizeof(Room *));

      const bool two_drop_rooms = (third_last_room->type == DROP_ROOM_CODE ||
                                   third_last_room->type == OPEN_ROOM_CODE) &&
                                  last_room->type == DROP_ROOM_CODE;

      if (two_drop_rooms) {
        last_room->type = OPEN_ROOM_CODE;
        mvwaddch(this->screen.window, last_room->start.y, last_room->start.x, last_room->type);
      }
    }

    // 1) Print to the screen the next_room
    // 2) Store the next room in the rooms vector
    // 3) Update the last room pointer
    mvwaddch(this->screen.window, next_room.start.y, next_room.start.x, next_room.type);
    this->rooms.emplace_back(next_room);
    last_room = &this->rooms.back();
  }

  // Change the code of the spawn and exit room
  this->rooms.front().type = SPAWN_ROOM_CODE;
  mvwaddch(this->screen.window,
           this->rooms.front().start.y,
           this->rooms.front().start.x,
           this->rooms.front().type);

  last_room->type = EXIT_ROOM_CODE;
  mvwaddch(this->screen.window,
           last_room->start.y,
           last_room->start.x,
           last_room->type);
}

std::string *Map::get_available_moves(const Room &last_room) {
  std::string *moves = new std::string("D");

  if (can_move(Coordinate(last_room.start.x - this->grid.width, last_room.start.y)))
    moves->append(1, 'L');

  if (can_move(Coordinate(last_room.start.x + this->grid.width, last_room.start.y)))
    moves->append(1, 'R');

  return moves;
}

const bool Map::can_move(const Coordinate &coordinate) {
  if (coordinate.x <= 0 || coordinate.y <= 0) return false;
  const char ch = mvwinch(this->screen.window, coordinate.y, coordinate.x) & A_CHARTEXT;
  return ch == ' ';
}

void Map::replace_solution_path() {
  for (int i = 0; i < this->number_rows; ++i) {
    for (int j = 0; j < this->number_columns; ++j) {
      const Coordinate start(
          (j * this->grid.width) + 1,
          (i * this->grid.height) + 1);

      const char room_type = mvwinch(this->screen.window, start.y, start.x) & A_CHARTEXT;
      const std::vector<std::string> *rooms = nullptr;

      if (room_type == CORRIDOR_ROOM_CODE) rooms = &Constants::Rooms::CORRIDOR;
      if (room_type == DROP_ROOM_CODE) rooms = &Constants::Rooms::DROP;
      if (room_type == LANDING_ROOM_CODE) rooms = &Constants::Rooms::LANDING;
      if (room_type == OPEN_ROOM_CODE) rooms = &Constants::Rooms::OPEN;
      if (room_type == SPAWN_ROOM_CODE) rooms = &Constants::Rooms::SPAWN;
      if (room_type == EXIT_ROOM_CODE) rooms = &Constants::Rooms::EXIT;

      this->add_room(start, rooms);
    }
  }
}

void Map::add_room(const Coordinate &start, const std::vector<std::string> *rooms) {
  const std::string *room = nullptr;
  unsigned int counter_room = 0;
  if (rooms && !rooms->empty()) {
    int idx_rooms = rand() % rooms->size();
    room = &rooms->at(idx_rooms);
  }

  for (int i = start.y; i < start.y + this->grid.height; ++i) {
    for (int j = start.x; j < start.x + this->grid.width; ++j) {
      char ch = 'X';

      if (room && counter_room < room->size()) {
        ch = room->at(counter_room++);

        if (ch == '0') ch = ' ';
        if (ch == '1') ch = '=';
        if (ch == '2') ch = rand() % 100 <= 70 ? ' ' : '=';
        if (ch == 'S' || ch == 'E') this->spawn_exit.emplace_back(j, i);
      }

      mvwaddch(this->screen.window, i, j, ch);
    }
  }
}

const Coordinate &Map::get_spawn() {
  return this->spawn_exit.front();
}

const Coordinate &Map::get_exit() {
  return this->spawn_exit.back();
}

}  // namespace Rush
