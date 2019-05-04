#ifndef LIGHT_CUBE_HPP
#define LIGHT_CUBE_HPP

#include "Cube.hpp"
#include "../Light.hpp"

class LightCube : public Cube, public Light {
  public:
    LightCube(AssetManager *am);
    ~LightCube();
};

#endif