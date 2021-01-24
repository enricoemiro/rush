#ifndef STATUS_HPP
#define STATUS_HPP

#include "../../Core/Struct/Screen.hpp"
#include "../../Utilities/Macros.hpp"
#include "../Scene.hpp"

namespace Rush {

class Status : public Scene {
 private:
  int& level;
  int& score;
  int& lives;

 public:
  Status(const Screen& screen, int& level, int& score, int& lives);
  void draw();
};

}  // namespace Rush

#endif
