add_library(vendor INTERFACE)

add_subdirectory(FTXUI)
add_subdirectory(spdlog)

target_include_directories(vendor INTERFACE FTXUI/include spdlog/include)

target_link_libraries(vendor INTERFACE ftxui::screen ftxui::dom ftxui::component)
