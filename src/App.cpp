#include "App.h"

App::App(sf::VideoMode mode, std::string title)
{
  _window.Create(mode, title);
}

App::~App()
{
}

void App::initialize()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, _window.GetWidth(), _window.GetHeight());

  glClearColor(0, 0, 0, 1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_CULL_FACE);
}

int App::run()
{
  return 0;
}
