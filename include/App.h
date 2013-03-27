#ifndef _APP_H_
#define _APP_H_

#include <iostream>

#include <SFML/Window.hpp>

class App
{
  protected:
    sf::Window _window;

    void handleEvent(sf::Event &event)
    {
      switch (event.Type) {
        case sf::Event::Closed:
          _window.Close();
          break;
        case sf::Event::Resized:
          handleResized(event.Size);
          break;
        case sf::Event::LostFocus:
          handleLostFocus();
          break;
        case sf::Event::GainedFocus:
          handleGainedFocus();
          break;
        case sf::Event::TextEntered:
          handleTextEntered(event.Text);
          break;
        case sf::Event::KeyPressed:
          handleKeyPressed(event.Key);
          break;
        case sf::Event::KeyReleased:
          handleKeyReleased(event.Key);
          break;
        case sf::Event::MouseWheelMoved:
          handleMouseWheelMoved(event.MouseWheel);
          break;
        case sf::Event::MouseButtonPressed:
          handleMousePressed(event.MouseButton);
          break;
        case sf::Event::MouseButtonReleased:
          handleMouseReleased(event.MouseButton);
          break;
        case sf::Event::MouseMoved:
          handleMouseMoved(event.MouseMove);
          break;
        case sf::Event::MouseEntered:
          handleMouseEntered();
          break;
        case sf::Event::MouseLeft:
          handleMouseLeft();
          break;
        case sf::Event::JoyButtonPressed:
          handleJoyButtonPressed(event.JoyButton);
          break;
        case sf::Event::JoyButtonReleased:
          handleJoyButtonReleased(event.JoyButton);
          break;
        case sf::Event::JoyMoved:
          handleJoyMoved(event.JoyMove);
          break;
        default:
          break;
      }
    }

    virtual void initialize() = 0;
    virtual void handleResized(sf::Event::SizeEvent &event) = 0;
    virtual void handleLostFocus() = 0;
    virtual void handleGainedFocus() = 0;
    virtual void handleTextEntered(sf::Event::TextEvent &event) = 0;
    virtual void handleKeyPressed(sf::Event::KeyEvent &event) = 0;
    virtual void handleKeyReleased(sf::Event::KeyEvent &event) = 0;
    virtual void handleMouseWheelMoved(sf::Event::MouseWheelEvent &event) = 0;
    virtual void handleMousePressed(sf::Event::MouseButtonEvent &event) = 0;
    virtual void handleMouseReleased(sf::Event::MouseButtonEvent &event) = 0;
    virtual void handleMouseMoved(sf::Event::MouseMoveEvent &event) = 0;
    virtual void handleMouseEntered() = 0;
    virtual void handleMouseLeft() = 0;
    virtual void handleJoyButtonPressed(sf::Event::JoyButtonEvent &event) = 0;
    virtual void handleJoyButtonReleased(sf::Event::JoyButtonEvent &event) = 0;
    virtual void handleJoyMoved(sf::Event::JoyMoveEvent &event) = 0;

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

  public:
    App(sf::VideoMode mode, std::string title)
    {
      _window.Create(mode, title);
    }

    virtual ~App()
    {
    }

    int run()
    {
      initialize();

      sf::Event event;

      while (_window.IsOpened()) {
        while (_window.GetEvent(event)) {
          handleEvent(event);
        }

        update(_window.GetFrameTime());
        draw();
      }

      return 0;
    }
};

#endif
