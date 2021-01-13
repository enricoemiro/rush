#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <iostream>
#include <string>
#include <vector>

class Constants {
 public:
  struct Rooms {
    static const std::vector<std::string> CORRIDOR;
    static const std::vector<std::string> DROP;
    static const std::vector<std::string> LANDING;
    static const std::vector<std::string> OPEN;
  };
};

#endif
