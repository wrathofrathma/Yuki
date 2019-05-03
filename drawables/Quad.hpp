#ifndef QUAD_HPP
#define QUAD_HPP

#include "Polygon.hpp"
#include "../AssetManager.hpp"
class Quad : public Polygon {
  private:
    glm::vec4 dimensions;
  public:
    Quad(AssetManager *am, float x=1.0, float y=1.0, float z=1.0, float w=1.0);
    ~Quad();
    void setDimensions(glm::vec4 dims);
    void generateQuad();
};

#endif
