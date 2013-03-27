#ifndef _SSAPP_H_
#define _SSAPP_H_

#include <string>
#include <utility>
#include <vector>

#include <SFML/Window.hpp>

#include "App.h"
#include "Model.h"

class SSApp
  : public App
{
  private:
    std::pair<int, int> _previousMouse;
    sf::Window _window;

    std::vector<float> _focus;
    std::vector<float> _rotationMatrix;

    Model _model;

  protected:
    void initialize();

    void handleResized(sf::Event::SizeEvent &event);
    void handleLostFocus() { }
    void handleGainedFocus() { }
    void handleTextEntered(sf::Event::TextEvent &event) { }
    void handleKeyPressed(sf::Event::KeyEvent &event);
    void handleKeyReleased(sf::Event::KeyEvent &event) { }
    void handleMouseWheelMoved(sf::Event::MouseWheelEvent &event) { }
    void handleMousePressed(sf::Event::MouseButtonEvent &event);
    void handleMouseReleased(sf::Event::MouseButtonEvent &event) { }
    void handleMouseMoved(sf::Event::MouseMoveEvent &event);
    void handleMouseEntered() { }
    void handleMouseLeft() { }
    void handleJoyButtonPressed(sf::Event::JoyButtonEvent &event) { }
    void handleJoyButtonReleased(sf::Event::JoyButtonEvent &event) { }
    void handleJoyMoved(sf::Event::JoyMoveEvent &event) { }

    void update(float dt);
    void draw();

  public:
    SSApp(sf::VideoMode mode, std::string title);
    SSApp(sf::VideoMode mode, std::string title, std::string filename);
    ~SSApp();
};

#endif
