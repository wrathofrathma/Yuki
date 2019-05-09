#ifndef LIGHT_CUBE_HPP
#define LIGHT_CUBE_HPP

#include "Cube.hpp"
#include "../components/Light.hpp"
/**
\file LightCube.hpp
\brief Header file for LightCube.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 5/8/2019

*/

/**
\class LightCube
\brief A convenience class combining the light component with a drawable cube.
*/
class LightCube : public Cube, public Light {
  public:
    LightCube(AssetManager *am);
    ~LightCube();
};

#endif
