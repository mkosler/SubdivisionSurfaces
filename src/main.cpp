#include <SFML/Window.hpp>

#include "App.h"

int main(int argc, char *argv[])
{
  App app(sf::VideoMode(500, 500, 32), "CSCE 645 - Michael Kosler");

  return app.run();
}
