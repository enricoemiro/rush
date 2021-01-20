#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <iostream>
#include <string>
#include <vector>

namespace Rush {

struct Constants {
  struct Rooms {
    static const std::vector<std::string> CORRIDOR;
    static const std::vector<std::string> DROP;
    static const std::vector<std::string> LANDING;
    static const std::vector<std::string> OPEN;

    // Special rooms
    static const std::vector<std::string> SPAWN_CORRIDOR;
    static const std::vector<std::string> SPAWN_DROP;
    static const std::vector<std::string> EXIT_CORRIDOR;
    static const std::vector<std::string> EXIT_LANDING;
  };
};

}  // namespace Rush

#endif
