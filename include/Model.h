#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Point.h"

class Model
{
  private:
    std::vector<Vertex> _vertexes;
    std::vector<Face> _faces;

    Vertex getNormal(Vertex v);

  public:
    Model();
    ~Model();

    void draw() const;

    static Model load(std::string filename);
    static void save(Model model, std::string filename);

    friend std::ostream &operator<<(std::ostream &os, const Model &m);
};

#endif
