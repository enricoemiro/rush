cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(
  rush
  VERSION 2.0.0
  DESCRIPTION "Project for the University of Bologna Programming course (a.y. 2020-21)."
  HOMEPAGE_URL "https://github.com/enricoemiro/rush"
  LANGUAGES CXX)

# Configure C++ settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS TRUE)

# Include the "vendor" and "src/Rush" directories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/Rush)

# Link with the "vendor" target to include external dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)

# Set precompiled headers for the target
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hh)
