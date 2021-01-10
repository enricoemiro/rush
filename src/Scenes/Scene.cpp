#include "Scene.hpp"

Scene::Scene(Screen *screen) {
  this->screen = screen;
}

Scene::~Scene() {
  if (this->screen->window)
    delwin(this->screen->window);
}

void Scene::draw_edges() {
  wborder(this->screen->window,
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
  wrefresh(this->screen->window);
}

void Scene::draw() {
  this->draw_edges();
  this->refresh();
}
