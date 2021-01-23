#include "Grid.hpp"

namespace Rush {

Grid::Grid(int width, int height) : width(width), height(height) {}

Grid::Grid(const Grid& other) : width(other.width), height(other.height) {}

}  // namespace Rush
