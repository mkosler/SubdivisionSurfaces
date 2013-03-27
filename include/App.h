#ifndef _APP_H_
#define _APP_H_

#include <string>
#include <utility>
#include <vector>

#include <SFML/Window.hpp>

#include "Model.h"

class App
{
  private:
    std::pair<int, int> _previousMouse;
    sf::Window _window;

    std::vector<float> _focus;
    std::vector<float> _rotationMatrix;

    Model _model;

    void initialize();

    void handleEvent(sf::Event &event);
    void handleResized(sf::Event::SizeEvent &event);
    void handleKeyPressed(sf::Event::KeyEvent &event);
    void handleMousePressed(sf::Event::MouseButtonEvent &event);
    void handleMouseMoved(sf::Event::MouseMoveEvent &event);

    void update(float dt);

    void draw();

  public:
    App(sf::VideoMode mode, std::string title);
    App(sf::VideoMode mode, std::string title, std::string filename);
    ~App();

    int run();
};

#endif
