#include <fstream>

#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

Model Model::load(std::string filename)
{
  std::ifstream ifs(filename.c_str());
  while (!ifs.eof()) {
    char flag;
  }
}

void Model::save(Model model, std::string filename)
{
}
