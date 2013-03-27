#include <iostream>

#include "App.h"
#include "Model.h"

App::App(sf::VideoMode mode, std::string title)
  : _previousMouse(std::pair<int, int>(0, 0))
{
  _window.Create(mode, title);

  _rotationMatrix.push_back(1);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(1);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);

  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(1);
  _rotationMatrix.push_back(0);

  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(1);

  _focus.push_back(0);
  _focus.push_back(0);
  _focus.push_back(-1.5);
}

App::App(sf::VideoMode mode, std::string title, std::string filename)
  : _previousMouse(std::pair<int, int>(0, 0)),
    _model(Model::load(filename))
{
  _window.Create(mode, title);

  _rotationMatrix.push_back(1);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(1);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);

  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(1);
  _rotationMatrix.push_back(0);

  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(0);
  _rotationMatrix.push_back(1);

  _focus.push_back(0);
  _focus.push_back(0);
  _focus.push_back(-1.5);
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

  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_CULL_FACE);
}

void App::handleEvent(sf::Event &event)
{
  switch (event.Type) {
    case sf::Event::Closed:
      _window.Close();
      break;
    case sf::Event::Resized:
      handleResized(event.Size);
      break;
    case sf::Event::KeyPressed:
      handleKeyPressed(event.Key);
      break;
    case sf::Event::MouseButtonPressed:
      handleMousePressed(event.MouseButton);
      break;
    case sf::Event::MouseMoved:
      handleMouseMoved(event.MouseMove);
      break;
    default:
      break;
  }
}

void App::handleResized(sf::Event::SizeEvent &event)
{
  glViewport(0, 0, event.Width, event.Height);
  _window.SetSize(event.Width, event.Height);
}

void App::handleKeyPressed(sf::Event::KeyEvent &event)
{
  switch (event.Code) {
    case sf::Key::O:
      {
        std::string filename;
        std::cout << "Enter the filename: ";
        std::cin >> filename;

        try {
          _model = Model::load(filename);
        } catch (std::exception &e) {
          std::cerr << e.what() << std::endl;
        }
      }
      break;
    case sf::Key::Escape:
      _window.Close();
      break;
    default:
      break;
  }
}

void App::handleMousePressed(sf::Event::MouseButtonEvent &event)
{
  _previousMouse.first = event.X; _previousMouse.second = _window.GetHeight() - event.Y;
}

void App::handleMouseMoved(sf::Event::MouseMoveEvent &event)
{
  int x = event.X,
      y = _window.GetHeight() - event.Y;

  float dx = x - _previousMouse.first,
        dy = y - _previousMouse.second;

  if (_window.GetInput().IsMouseButtonDown(sf::Mouse::Left)) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(dx, 0, 1, 0);
    glRotatef(dy, -1, 0, 0);
    glMultMatrixf(&_rotationMatrix[0]);
    glGetFloatv(GL_MODELVIEW_MATRIX, &_rotationMatrix[0]);
  } else if (_window.GetInput().IsMouseButtonDown(sf::Mouse::Middle)) {
    _focus[0] += 0.005f * dx;
    _focus[1] += 0.005f * dy;
  } else if (_window.GetInput().IsMouseButtonDown(sf::Mouse::Right)) {
    _focus[2] += 0.01f * dy;
  }

  _previousMouse.first = x;
  _previousMouse.second = y;
}

void App::update(float dt)
{
}

void App::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set up viewing matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, float(_window.GetWidth()) / _window.GetHeight(), 0.0001, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(_focus[0], _focus[1], _focus[2]);
  glMultMatrixf(&_rotationMatrix[0]);

  _model.draw();

  _window.Display();
}

int App::run()
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
