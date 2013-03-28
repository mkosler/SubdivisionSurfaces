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

    Vertex getFaceNormal(Vertex v1, Vertex v2, Vertex v3) const;
    Vertex getCentroid(Vertex v1, Vertex v2, Vertex v3, Vertex v4) const;

  public:
    Model();
    ~Model();

    std::vector<Face> subdivide(std::vector<Vertex> &vertexes, std::vector<Face> faces);
    std::vector<Vertex> average(std::vector<Vertex> vertexes, std::vector<Face> &faces);

    void draw() const;

    static Model load(std::string filename);
    static void save(Model model, std::string filename);

    friend std::ostream &operator<<(std::ostream &os, const Model &m);
};

#endif
