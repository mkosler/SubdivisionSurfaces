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

Vertex Model::getFaceNormal(Vertex v1, Vertex v2, Vertex v3) const
{
  Vertex vec1 = v3 - v2;
  Vertex vec2 = v1 - v2;

  Vertex normal;
  normal[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
  normal[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
  normal[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

  normal.normalize();

  return normal;
}

void Model::draw() const
{
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
    for (size_t i = 0; i < _faces.size(); i++) {
      Face f = _faces[i];

      Vertex vx = _vertexes[f[0] - 1],
             vy = _vertexes[f[1] - 1],
             vz = _vertexes[f[2] - 1],
             vw = _vertexes[f[3] - 1];

      Vertex normal = getFaceNormal(vx, vy, vz);
      glNormal3f(normal[0], normal[1], normal[2]);

      glVertex3f(vx[0], vx[1], vx[2]);
      glVertex3f(vy[0], vy[1], vy[2]);
      glVertex3f(vz[0], vz[1], vz[2]);
      glVertex3f(vw[0], vw[1], vw[2]);
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
          iss >> v[0] >> v[1] >> v[2];
          m._vertexes.push_back(v);
        }
        break;
      case 'f':
        {
          Face f;
          iss >> f[0] >> f[1] >> f[2] >> f[3];
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
    Vertex v = m._vertexes[i];
    os << v[0] << ' ' << v[1] << ' ' << v[2] << std::endl;
  }

  os << "### Faces (" << m._faces.size() << ") ###" << std::endl;
  for (size_t i = 0; i < m._faces.size(); i++) {
    Face f = m._faces[i];
    os << f[0] << ' ' << f[1] << ' ' << f[2] << ' ' << f[3] << std::endl;
  }

  return os;
}
