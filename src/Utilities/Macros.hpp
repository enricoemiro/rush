#ifndef MACROS_HPP
#define MACROS_HPP

#include <iostream>

namespace Rush {

#define DEBUG 1
#define EXIT_IF_TRUE(expression, msg) \
  {                                   \
    if (expression) {                 \
      endwin();                       \
      std::cout << msg << std::endl;  \
      exit(EXIT_FAILURE);             \
    }                                 \
  }

}  // namespace Rush

#endif
