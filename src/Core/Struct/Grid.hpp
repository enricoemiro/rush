#ifndef GRID_HPP
#define GRID_HPP

namespace Rush {

struct Grid {
  int width,
      height;

  Grid(int width,
       int height);
  Grid(const Grid &other);
};

}  // namespace Rush

#endif
