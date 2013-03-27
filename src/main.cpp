#include <string>

#include <SFML/Window.hpp>

#include "App.h"

int main(int argc, char *argv[])
{
  if (argc > 1) {
    App app(sf::VideoMode(500, 500, 32), "CSCE 645 - Michael Kosler", std::string(argv[1]));
    return app.run();
  } else {
    App app(sf::VideoMode(500, 500, 32), "CSCE 645 - Michael Kosler");
    return app.run();
  }
}
