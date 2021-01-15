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
    static const std::vector<std::string> SPAWN;
    static const std::vector<std::string> EXIT;
  };
};

}  // namespace Rush

#endif
