#include "UI.hpp"

namespace Rush {
UI::UI(const Screen& screen) : Scene(screen) {
  this->score = 1;
}

void UI::game_over() {
  while (!this->press_esc(getch())) {
    this->draw();

    std::string game_over = "GAME OVER";
    wattron(this->screen.window, A_BOLD);
    mvwprintw(this->screen.window, this->screen.size.height / 2.2,
              (this->screen.size.width - game_over.length()) / 2,
              game_over.c_str());
    wattroff(this->screen.window, A_BOLD);

    std::string score_string = "SCORE: ";
    mvwprintw(this->screen.window, (this->screen.size.height / 4) * 2,
              (this->screen.size.width - score_string.length()) / 2 - 1,
              "SCORE: %d", this->score);

    std::string exit = "PRESS ESC BUTTON TO EXIT";
    mvwprintw(this->screen.window, (this->screen.size.height / 4) * 3 + 1,
              (this->screen.size.width - exit.length()) / 2, exit.c_str());
  }
  wclear(this->screen.window);
}

void UI::initial_screen() {
  while (!this->press_enter(getch())) {
    this->draw();

    std::string game_title = "RUSH";
    wattron(this->screen.window, A_REVERSE);
    mvwprintw(this->screen.window, this->screen.size.height / 3,
              (this->screen.size.width - game_title.length()) / 2,
              game_title.c_str());
    wattroff(this->screen.window, A_REVERSE);

    std::string credits = "A GAME DEVELOPED BY:";
    std::string ee = "ENRICO EMIRO";
    std::string st = "SIMONE TASSI";

    mvwprintw(this->screen.window, this->screen.size.height / 3 + 2,
              (this->screen.size.width - credits.length()) / 2,
              credits.c_str());
    mvwprintw(this->screen.window, this->screen.size.height / 3 + 3,
              (this->screen.size.width - ee.length()) / 2, ee.c_str());
    mvwprintw(this->screen.window, this->screen.size.height / 3 + 4,
              (this->screen.size.width - st.length()) / 2, st.c_str());

    std::string start = "PRESS ENTER BUTTON TO START";
    wattron(this->screen.window, A_BLINK);
    mvwprintw(this->screen.window, (this->screen.size.height / 4) * 3 + 1,
              (this->screen.size.width - start.length()) / 2, start.c_str());
    wattroff(this->screen.window, A_BLINK);
  }
  wclear(this->screen.window);
}

void UI::set_score(int score) {
  this->score = score;
}

bool UI::press_enter(const int key_pressed) {
  return key_pressed == 10;
}
bool UI::press_esc(const int key_pressed) {
  return key_pressed == 27;
}

}  // namespace Rush
