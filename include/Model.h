#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class Model
{
  public:
    typedef sf::Vector3<float> Vertex;

    struct Face
    {
      int x, y, z, w;
    };

  private:
    std::vector<Vertex> _vertexes;
    std::vector<Face> _faces;

  public:
    Model();
    ~Model();

    void draw() const;

    static Model load(std::string filename);
    static void save(Model model, std::string filename);

    friend std::ostream &operator<<(std::ostream &os, const Model &m);
};

#endif
