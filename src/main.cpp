#include <string>

#include <SFML/Window.hpp>

#include "SSApp.h"

int main(int argc, char *argv[])
{
  if (argc > 1) {
    SSApp app(sf::VideoMode(500, 500, 32), "CSCE 645 - Michael Kosler", std::string(argv[1]));
    return app.run();
  } else {
    SSApp app(sf::VideoMode(500, 500, 32), "CSCE 645 - Michael Kosler");
    return app.run();
  }
}
