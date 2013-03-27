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
          iss >> f.X >> f.Y >> f.Z >> f.W;
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
}
