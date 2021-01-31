#include "Constants.hpp"

namespace Rush {

const std::vector<std::string> Constants::Rooms::CORRIDOR = {
    "LB000000BL"
    "1102222011"
    "0000LB0000"
    "0022112200"
    "0000000000"
    "2222002222"
    "0000000000"
    "3333333333"};

const std::vector<std::string> Constants::Rooms::DROP = {
    "0000000000"
    "0222222220"
    "0000BB0000"
    "0220110220"
    "0000000000"
    "0001111000"
    "0000000000"
    "3333003333"};

const std::vector<std::string> Constants::Rooms::LANDING = {
    "0000L00000"
    "2211122000"
    "00000B0000"
    "0002211122"
    "0000L00000"
    "2211122000"
    "0000000000"
    "3333333333"};

const std::vector<std::string> Constants::Rooms::OPEN = {
    "0000000000"
    "0222222220"
    "0000000000"
    "0022222200"
    "0000000000"
    "0001111000"
    "0000000000"
    "3333003333"};

const std::vector<std::string> Constants::Rooms::SPAWN_CORRIDOR = {
    "0000SL0000"
    "0222112220"
    "00L0000L00"
    "0212112120"
    "0000000000"
    "0222222220"
    "0000BB0000"
    "3333333333"};

const std::vector<std::string> Constants::Rooms::SPAWN_DROP = {
    "0000SL0000"
    "0001111000"
    "000L00L000"
    "2221001222"
    "0000LL0000"
    "0021111200"
    "0000000000"
    "3333003333"};

const std::vector<std::string> Constants::Rooms::EXIT_CORRIDOR = {
    "0000000000"
    "0222222220"
    "0000000000"
    "0222222220"
    "0000000000"
    "0222222220"
    "0000LE0000"
    "3333333333"};

const std::vector<std::string> Constants::Rooms::EXIT_LANDING = {
    "0000000000"
    "0222222220"
    "0000000000"
    "0022222200"
    "00B0000B00"
    "0012222100"
    "00000E0000"
    "3333333333"};

const char Constants::Game::WALL_CHAR = '/';
const char Constants::Game::SPACE_CHAR = ' ';
const char Constants::Game::PLAYER_CHAR = '&';
const char Constants::Game::BLOCK_CHAR = '#';
const char Constants::Game::FLOOR_CHAR = '=';
const char Constants::Game::BONUS_CHAR = 'B';
const char Constants::Game::LIFE_CHAR = 'L';

}  // namespace Rush
