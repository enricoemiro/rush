#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <iostream>
#include <string>
#include <vector>

/**
 * Map grid layouts
 * 
 * Each grid has a size of 10x8 + 1. The most significant bit
 * represents if the grid is symmetrical or asymmetrical.
 * The rest represent the actual layout of the grid.
 */

extern const std::vector<std::string> OPEN_ROOMS;
extern const std::vector<std::string> CORRIDOR_ROOMS;
extern const std::vector<std::string> DROP_ROOMS;
extern const std::vector<std::string> LANDING_ROOMS;

#endif
