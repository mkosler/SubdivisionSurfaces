#include <iostream>
#include <fstream>
#include <sstream>

#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::draw() const
{
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
    for (size_t i = 0; i < _faces.size(); i++) {
      Face f = _faces[i];

      Vertex vx = _vertexes[f.x - 1],
             vy = _vertexes[f.y - 1],
             vz = _vertexes[f.z - 1],
             vw = _vertexes[f.w - 1];

      glVertex3f(vx.x, vx.y, vx.z);
      glVertex3f(vy.x, vy.y, vy.z);
      glVertex3f(vz.x, vz.y, vz.z);
      glVertex3f(vw.x, vw.y, vw.z);
    }
  glEnd();
}

Model Model::load(std::string filename)
{
  Model m;

  std::ifstream ifs(filename.c_str());
  while (!ifs.eof()) {
    std::string line;
    std::getline(ifs, line);

    std::istringstream iss(line);
    char flag;

    iss >> flag;
    switch (flag) {
      case '#':
        // Ignore this whole line
        break;
      case 'v':
        {
          Vertex v;
          iss >> v.x >> v.y >> v.z;
          m._vertexes.push_back(v);
        }
        break;
      case 'f':
        {
          Face f;
          iss >> f.x >> f.y >> f.z >> f.w;
          m._faces.push_back(f);
        }
        break;
      default:
        std::cerr << "Unknown flag: " << line[0] << std::endl;
        break;
    }
  }

  ifs.close();

  return m;
}

void Model::save(Model model, std::string filename)
{
}

std::ostream &operator<<(std::ostream &os, const Model &m)
{
  os << "### Vertexes (" << m._vertexes.size() << ") ###" << std::endl;
  for (size_t i = 0; i < m._vertexes.size(); i++) {
    Model::Vertex v = m._vertexes[i];
    os << v.x << ' ' << v.y << ' ' << v.z << std::endl;
  }

  os << "### Faces (" << m._faces.size() << ") ###" << std::endl;
  for (size_t i = 0; i < m._faces.size(); i++) {
    Model::Face f = m._faces[i];
    os << f.x << ' ' << f.y << ' ' << f.z << ' ' << f.w << std::endl;
  }

  return os;
}
