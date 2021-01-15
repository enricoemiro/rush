#include "Scene.hpp"

namespace Rush {

Scene::Scene(const Screen &screen)
    : screen(screen) {}

void Scene::draw_edges() {
  wborder(this->screen.window,
          ACS_VLINE,
          ACS_VLINE,
          ACS_HLINE,
          ACS_HLINE,
          ACS_ULCORNER,
          ACS_URCORNER,
          ACS_LLCORNER,
          ACS_LRCORNER);
}

void Scene::refresh() {
  wrefresh(this->screen.window);
}

void Scene::draw() {
  this->draw_edges();
  this->refresh();
}

}  // namespace Rush
