#include "Map.hpp"

namespace Rush {

// Map constants
const char Map::CORRIDOR_ROOM_CODE = '1';
const char Map::DROP_ROOM_CODE = '2';
const char Map::LANDING_ROOM_CODE = '3';
const char Map::OPEN_ROOM_CODE = '4';
const char Map::SPAWN_CORRIDOR_ROOM_CODE = '5';
const char Map::SPAWN_DROP_ROOM_CODE = '6';
const char Map::EXIT_CORRIDOR_ROOM_CODE = '7';
const char Map::EXIT_LANDING_ROOM_CODE = '8';

Map::Map(const Screen& screen, const Grid& grid) : Scene(screen), grid(grid) {
  EXIT_IF_TRUE(this->screen.size.width < grid.width ||
                   this->screen.size.height < grid.height,
               "The screen must have a minimum size of " << grid.width << "x"
                                                         << grid.height);

  EXIT_IF_TRUE(this->screen.size.width % grid.width != 0,
               "The width of the screen must be divisible by" << grid.width);

  EXIT_IF_TRUE(this->screen.size.width % grid.height != 0,
               "The height of the screen must be divisible by " << grid.height)

  this->number_columns = this->screen.size.width / this->grid.width;
  this->number_rows = this->screen.size.height / this->grid.height;
  this->rooms.reserve(this->number_columns * this->number_rows);
  this->spawn_exit.reserve(2);
}

void Map::print_room(const Room& room) {
  mvwaddch(this->screen.window, room.start.y, room.start.x, room.type);
}

char Map::get_character(const Coordinate& coordinate) {
  return mvwinch(this->screen.window, coordinate.y, coordinate.x) & A_CHARTEXT;
}

void Map::draw() {
  this->draw_edges();
  this->generate_solution_path();
  this->replace_solution_path();
  this->refresh();
}

void Map::generate_solution_path() {
  // Place the spawn room in the top row
  this->rooms.push_back(
      {this->CORRIDOR_ROOM_CODE,
       {rand() % this->number_columns * this->grid.width + 1, 1}});

  this->print_room(this->rooms.front());

  // Keeps track of the last room placed
  Room* last_room = &this->rooms.front();

  while (true) {
    Room next_room(CORRIDOR_ROOM_CODE, last_room->start);
    char move_ch = get_move(next_room);

    // Move the solution path
    this->move(*last_room, next_room, move_ch);

    // Stop the generation
    if (next_room.start.y >= this->screen.size.height) {
      this->update_spawn_type();
      this->update_exit_type();

      break;
    }

    // Print to the screen the new room
    // Save the new room in the rooms vector
    // Update the last room pointer
    this->print_room(next_room);
    this->rooms.emplace_back(next_room);
    last_room = last_room + 1;
  }

  // If there are two consecutive rooms of type 2,
  // the type of the second one is replaced with 4
  for (auto& current_room : this->rooms) {
    if (&current_room == last_room)
      break;

    auto next_room = *(&current_room + 1);
    const bool two_drop_rooms_in_row =
        (current_room.type == this->DROP_ROOM_CODE ||
         current_room.type == this->OPEN_ROOM_CODE ||
         current_room.type == this->SPAWN_DROP_ROOM_CODE) &&
        next_room.type == this->DROP_ROOM_CODE;

    if (two_drop_rooms_in_row) {
      next_room.type = this->OPEN_ROOM_CODE;
      this->print_room(next_room);
    }
  }
}

bool Map::can_move(const Coordinate& coordinate) {
  if (coordinate.x <= 0 || coordinate.y <= 0)
    return false;

  return this->get_character(coordinate) == ' ';
}

std::string Map::get_available_moves(const Room& room) {
  std::string moves("D");

  if (can_move({room.start.x - this->grid.width, room.start.y}))
    moves.append(1, 'L');

  if (can_move({room.start.x + this->grid.width, room.start.y}))
    moves.append(1, 'R');

  return moves;
}

char Map::get_move(const Room& room) {
  std::string moves = this->get_available_moves(room);

  return moves.at(rand() % moves.size());
}

void Map::move(Room& last_room, Room& room, char move_ch) {
  // clang-format off
  if (move_ch == 'R') this->move_right(room);
  if (move_ch == 'L') this->move_left(room);
  if (move_ch == 'D') this->move_down(last_room, room);
  // clang-format on
}

void Map::move_right(Room& room) {
  room.start.x += this->grid.width;
}

void Map::move_left(Room& room) {
  room.start.x -= this->grid.width;
}

void Map::move_down(Room& last_room, Room& room) {
  room.start.y += this->grid.height;

  last_room.type = this->DROP_ROOM_CODE;
  this->print_room(last_room);
  room.type = this->LANDING_ROOM_CODE;
}

void Map::update_spawn_type() {
  this->rooms.front().type =
      this->rooms.front().type == this->CORRIDOR_ROOM_CODE
          ? this->SPAWN_CORRIDOR_ROOM_CODE
          : this->SPAWN_DROP_ROOM_CODE;

  this->print_room(this->rooms.front());
}

void Map::update_exit_type() {
  char penultimate_room_type = this->rooms[this->rooms.size() - 2].type;

  this->rooms.back().type =
      (penultimate_room_type == this->CORRIDOR_ROOM_CODE ||
       penultimate_room_type == this->LANDING_ROOM_CODE)
          ? this->EXIT_CORRIDOR_ROOM_CODE
          : this->EXIT_LANDING_ROOM_CODE;

  this->print_room(this->rooms.back());
}

const std::vector<std::string>* Map::get_room_templates(char room_type) {
  switch (room_type) {
    case this->CORRIDOR_ROOM_CODE:
      return &Constants::Rooms::CORRIDOR;

    case this->DROP_ROOM_CODE:
      return &Constants::Rooms::DROP;

    case this->LANDING_ROOM_CODE:
      return &Constants::Rooms::LANDING;

    case this->OPEN_ROOM_CODE:
      return &Constants::Rooms::OPEN;

    case this->SPAWN_CORRIDOR_ROOM_CODE:
      return &Constants::Rooms::SPAWN_CORRIDOR;

    case this->SPAWN_DROP_ROOM_CODE:
      return &Constants::Rooms::SPAWN_DROP;

    case this->EXIT_CORRIDOR_ROOM_CODE:
      return &Constants::Rooms::EXIT_CORRIDOR;

    case this->EXIT_LANDING_ROOM_CODE:
      return &Constants::Rooms::EXIT_LANDING;

    default:
      return nullptr;
  }
}

const std::string* Map::get_room_template(
    const std::vector<std::string>* rooms) {
  if (rooms && rooms->size() != 0)
    return &rooms->at(rand() % rooms->size());

  return nullptr;
}

void Map::add_rooms(int row) {
  for (int j = 0; j < this->number_columns; ++j) {
    const Coordinate room_coordinate(j * this->grid.width + 1,
                                     row * this->grid.height + 1);

    const char room_type = this->get_character(room_coordinate);
    const std::vector<std::string>* rooms = this->get_room_templates(room_type);

    this->add_room(room_coordinate, rooms);
  }
}

void Map::replace_solution_path() {
  for (int i = 0; i < this->number_rows; ++i)
    this->add_rooms(i);
}

void Map::add_room(const Coordinate& start,
                   const std::vector<std::string>* rooms) {
  const std::string* room = this->get_room_template(rooms);
  unsigned int counter_room = 0;

  for (int i = start.y; i < start.y + this->grid.height; ++i) {
    for (int j = start.x; j < start.x + this->grid.width; ++j) {
      char ch = 'X';

      if (room) {
        ch = room->at(counter_room++);

        // clang-format off
        if (ch == '0') ch = ' ';
        if (ch == '1') ch = '=';
        if (ch == '2') ch = rand() % 100 <= 60 ? ' ' : '=';
        if (ch == 'S' || ch == 'E') this->spawn_exit.emplace_back(j, i);
				if (ch == 'B') ch = rand() % 100 <= 30 ? 'B' : ' ';
				if (ch == 'L') ch = rand() % 100 <= 20 ? 'L' : ' ';
        // clang-format on
      }

      mvwaddch(this->screen.window, i, j, ch);
    }
  }
}

const Coordinate& Map::get_spawn() const {
  return this->spawn_exit.front();
}

const Coordinate& Map::get_exit() const {
  return this->spawn_exit.back();
}

const std::vector<Room>& Map::get_rooms_vector() const {
  return this->rooms;
}

const Grid& Map::get_grid() const {
  return this->grid;
}

}  // namespace Rush
