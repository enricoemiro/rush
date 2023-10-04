cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(
  rush
  VERSION 2.0.0
  DESCRIPTION "Project for the University of Bologna Programming course (a.y. 2020-21)."
  HOMEPAGE_URL "https://github.com/enricoemiro/rush"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS TRUE)

add_subdirectory(vendor)
add_subdirectory(src/Rush)

target_link_libraries(${PROJECT_NAME} PRIVATE vendor)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.hh)
