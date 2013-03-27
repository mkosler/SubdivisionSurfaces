#include <SFML/Window.hpp>

#include "SSApp.h"

int main(int argc, char *argv[])
{
  SSApp app(sf::VideoMode(500, 500, 32), "CSCE 645 - Michael Kosler");

  return app.run();
}
