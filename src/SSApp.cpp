#include <iostream>

#include "SSApp.h"

SSApp::SSApp(sf::VideoMode mode, std::string title)
  : App(mode, title),
    _previousMouse(std::pair<int, int>(0, 0))
{
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

SSApp::SSApp(sf::VideoMode mode, std::string title, std::string filename)
  : App(mode, title),
    _previousMouse(std::pair<int, int>(0, 0)),
    _model(Model::load(filename))
{
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

SSApp::~SSApp()
{
}

void SSApp::initialize()
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

void SSApp::handleResized(sf::Event::SizeEvent &event)
{
  glViewport(0, 0, event.Width, event.Height);
  _window.SetSize(event.Width, event.Height);
}

void SSApp::handleKeyPressed(sf::Event::KeyEvent &event)
{
  switch (event.Code) {
    case sf::Key::L:
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
    case sf::Key::Space:
      std::cout << _model << std::endl;
      break;
    default:
      break;
  }
}

void SSApp::handleMousePressed(sf::Event::MouseButtonEvent &event)
{
  _previousMouse.first = event.X; _previousMouse.second = _window.GetHeight() - event.Y;
}

void SSApp::handleMouseMoved(sf::Event::MouseMoveEvent &event)
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

void SSApp::update(float dt)
{
}

void SSApp::draw() const
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
}
