#ifndef MENEMY_HPP
#define MENEMY_HPP

#include "../../Scenes/Game/Status.hpp"
#include "Enemy.hpp"

namespace Rush {

class MEnemy : public Enemy {
 private:
  struct SingleEnemy {
    char direction;
    Coordinate current, previous;
  };

 protected:
  std::vector<SingleEnemy> enemies;
  Status* status;
  void update_positions();
  void draw_updated();
  void spawn_conditions(const Coordinate& coordinate) override;
  void move_left(SingleEnemy& enemy);
  bool can_move_left(SingleEnemy& enemy);
  void move_right(SingleEnemy& enemy);
  bool can_move_right(SingleEnemy& enemy);

 public:
  MEnemy(WINDOW* map_window, const Grid& grid, char symbol);
  void update_enemies();

  // SETTERS
  void set_status(Status* status);
};

}  // namespace Rush

#endif
