add_library(vendor INTERFACE)

target_include_directories(vendor INTERFACE ncurses/include spdlog/include)
