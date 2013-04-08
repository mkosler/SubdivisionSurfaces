#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <utility>

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

Vertex Model::getCentroid(Vertex v1, Vertex v2, Vertex v3, Vertex v4) const
{
  return (v1 + v2 + v3 + v4) / 4.0f;
}

std::vector<Face> Model::subdivide(std::vector<Vertex> &vertexes, std::vector<Face> faces)
{
  std::vector<Face> nFaces;
  std::map<std::pair<int, int>, int> hash;

  for (size_t i = 0; i < faces.size(); i++) {
    Face f = faces[i];

    unsigned e[4] = { 0 };
    for (size_t j = 0; j < 4; j++) {
      std::pair<int, int> p =
        std::make_pair(std::min(f[j], f[(j + 1) % f.size()]),
                       std::max(f[j], f[(j + 1) % f.size()]));

      std::map<std::pair<int, int>, int>::iterator it = hash.find(p);
      if (it == hash.end()) {
        vertexes.push_back((vertexes[p.first - 1] + vertexes[p.second - 1]) / 2.0f);
        hash[p] = vertexes.size();
      }

      e[j] = hash[p];
    }

    vertexes.push_back(
      getCentroid(
        vertexes[e[0] - 1],
        vertexes[e[2] - 1],
        vertexes[e[1] - 1],
        vertexes[e[3] - 1]));
    unsigned c = vertexes.size();

    for (size_t j = 0; j < 4; j++) {
      float ff[4] = {
        f[j],
        static_cast<float>(e[j]),
        static_cast<float>(c),
        static_cast<float>(e[(j - 1) % 4])
      };
      nFaces.push_back(Face(ff));
    }
  }

  return nFaces;
}

std::vector<Vertex> Model::average(std::vector<Vertex> vertexes, std::vector<Face> &faces)
{
  std::vector<Vertex> nVertexes(vertexes.size(), Vertex());
  std::vector<unsigned> valence(vertexes.size(), 0);

  for (size_t i = 0; i < faces.size(); i++) {
    Face f = faces[i];
    Vertex centroid = getCentroid(
        vertexes[f[0] - 1],
        vertexes[f[1] - 1],
        vertexes[f[2] - 1],
        vertexes[f[3] - 1]);

    for (size_t j = 0; j < 4; j++) {
      nVertexes[f[j] - 1] += centroid;
      valence[f[j] - 1]++;
    }
  }

  for (size_t i = 0; i < nVertexes.size(); i++) {
    nVertexes[i] /= valence[i];
  }

  return nVertexes;
}

void Model::performSubdivision()
{
  _faces = subdivide(_vertexes, _faces);
}

void Model::performAveraging()
{
  _vertexes = average(_vertexes, _faces);
}

void Model::draw() const
{
  glLineWidth(10.0f);
  for (size_t i = 0; i < _faces.size(); i++) {
    Face f = _faces[i];

    Vertex vx = _vertexes[f[0] - 1],
           vy = _vertexes[f[1] - 1],
           vz = _vertexes[f[2] - 1],
           vw = _vertexes[f[3] - 1];

    Vertex normal = getFaceNormal(vx, vy, vz);
    glNormal3f(normal[0], normal[1], normal[2]);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
      glVertex3f(vx[0], vx[1], vx[2]);
      glVertex3f(vy[0], vy[1], vy[2]);
      glVertex3f(vz[0], vz[1], vz[2]);
      glVertex3f(vw[0], vw[1], vw[2]);
    glEnd();

    //glColor3f(1.0f, 0.0f, 0.0f);
    //glBegin(GL_LINE_LOOP);
      //glVertex3f(vx[0], vx[1], vx[2]);
      //glVertex3f(vy[0], vy[1], vy[2]);
      //glVertex3f(vz[0], vz[1], vz[2]);
      //glVertex3f(vw[0], vw[1], vw[2]);
    //glEnd();
  }
}

Model Model::load(std::string filename)
{
  Model m;

  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()) {
    throw std::runtime_error("Unable to open file: " + filename);
  }

  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);

    char flag;
    if (!(iss >> flag)) {
      break;
    }
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
        throw std::runtime_error("Unknown flag for simple .obj: " + flag);
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
