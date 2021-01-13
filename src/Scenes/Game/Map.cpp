#include "Map.hpp"

Map::Map(Screen *screen, Grid *grid) : Scene(screen) {
  EXIT_IF_TRUE(this->screen->width < grid->width ||
                   this->screen->height < grid->height,
               "The screen must have a minimum size of "
                   << grid->width << "x" << grid->height);

  EXIT_IF_TRUE(this->screen->width % grid->width != 0,
               "The width of the screen must be divisible by" << grid->width);

  EXIT_IF_TRUE(this->screen->width % grid->height != 0,
               "The height of the screen must be divisible by " << grid->height)

  this->grid = grid;
  this->grids_per_width = this->screen->width / this->grid->width;
  this->grids_per_height = this->screen->height / this->grid->height;
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
                         ((rand() % this->grids_per_width) * this->grid->width) + 1,
                         1});

  // Print the spawn type room to the screen
  mvwaddch(this->screen->window, this->rooms[0].start_y, this->rooms[0].start_x, this->rooms[0].type);

  // Keeps track of the last room placed
  // (at the beginning it points to the spawn room)
  Room *last_room = &this->rooms[0];

  while (true) {
    // Make a copy of the last room placed
    Room *next_room = new Room(CORRIDOR_ROOM_CODE,
                               last_room->start_x,
                               last_room->start_y);

    const std::string *moves = get_available_moves(next_room);
    const int move_idx = rand() % moves->size();
    const char move_ch = moves->at(move_idx);
    delete moves;

    // The solution path moves right
    if (move_ch == 'R') next_room->start_x += this->grid->width;

    // The solution path moves left
    if (move_ch == 'L') next_room->start_x -= this->grid->width;

    // The solution path moves down
    if (move_ch == 'D') {
      next_room->start_y += this->grid->height;

      // If the new ordinate exceed the screen height,
      // draw the exit and stop the generation
      if (next_room->start_y >= this->screen->height) {
        delete next_room;
        break;
      }

      // Update the last room to be type 2 and print it to the screen
      this->rooms.back().type = DROP_ROOM_CODE;
      mvwaddch(this->screen->window, last_room->start_y, last_room->start_x, last_room->type);

      // The next room MUST be type 3
      next_room->type = LANDING_ROOM_CODE;
    }

    // 1) Print to the screen the next_room
    // 2) Store the next room in the rooms vector
    // 3) Update the last room pointer
    // 4) Free the memory of the next_room
    mvwaddch(this->screen->window, next_room->start_y, next_room->start_x, next_room->type);
    this->rooms.push_back(*next_room);
    last_room = &this->rooms.back();
    delete next_room;
  }

  // If there are two consecutive rooms of type 2,
  // the type of the second one is replaced with 4
  for (auto &current_room : this->rooms) {
    auto next_room = *(&current_room + 1);

    if ((current_room.type == DROP_ROOM_CODE ||
         current_room.type == OPEN_ROOM_CODE) &&
        next_room.type == DROP_ROOM_CODE) {
      next_room.type = OPEN_ROOM_CODE;
      mvwaddch(this->screen->window, next_room.start_y, next_room.start_x, next_room.type);
    }
  }

#if DEBUG == 1
  endwin();
  for (auto &room : this->rooms)
    std::cout << room << std::endl;
#endif
}

std::string *Map::get_available_moves(Room *last_room) {
  std::string *moves = new std::string("D");

  if (can_move(last_room->start_x - this->grid->width, last_room->start_y))
    moves->append(1, 'L');

  if (can_move(last_room->start_x + this->grid->width, last_room->start_y))
    moves->append(1, 'R');

  return moves;
}

const bool Map::can_move(int x, int y) {
  if (x <= 0 || y <= 0) return false;

  const char ch = mvwinch(this->screen->window, y, x) & A_CHARTEXT;

  return ch == ' ';
}

void Map::replace_solution_path() {
  for (int i = 0; i < this->grids_per_height; ++i) {
    for (int j = 0; j < this->grids_per_width; ++j) {
      int start_x = (j * this->grid->width) + 1;
      int start_y = (i * this->grid->height) + 1;

      const char room_type = mvwinch(this->screen->window, start_y, start_x) & A_CHARTEXT;
      const std::vector<std::string> *rooms = nullptr;

      if (room_type == CORRIDOR_ROOM_CODE) rooms = &CORRIDOR_ROOMS;
      if (room_type == DROP_ROOM_CODE) rooms = &DROP_ROOMS;
      if (room_type == LANDING_ROOM_CODE) rooms = &LANDING_ROOMS;
      if (room_type == OPEN_ROOM_CODE) rooms = &OPEN_ROOMS;

      this->add_room(start_x, start_y, rooms);
    }
  }
}

void Map::add_room(int start_x, int start_y, const std::vector<std::string> *rooms) {
  const std::string *room = nullptr;
  unsigned int counter_room = 0;
  if (rooms && !rooms->empty()) {
    int idx_rooms = rand() % rooms->size();
    room = &rooms->at(idx_rooms);
  }

  for (int i = start_y; i < start_y + this->grid->height; ++i) {
    for (int j = start_x; j < start_x + this->grid->width; ++j) {
      char ch = 'X';

      if (room && counter_room < room->size()) {
        ch = room->at(counter_room++);

        if (ch == '0') ch = ' ';
        if (ch == '1') ch = '=';
      }

      mvwaddch(this->screen->window, i, j, ch);
    }
  }
}
