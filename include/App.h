#ifndef _APP_H_
#define _APP_H_

#include <string>

#include <SFML/Window.hpp>

class App
{
  private:
    sf::Window _window;

    void initialize();

  public:
    App(sf::VideoMode mode, std::string title);
    ~App();

    int run();
};

#endif
