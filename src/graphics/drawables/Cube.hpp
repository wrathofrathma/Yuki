#ifndef CUBE_HPP
#define CUBE_HPP
#include "../components/Drawable.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
/**
\file Cube.hpp
\brief Header file for Cube.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 5/8/2019

*/

/**
\class Cube
\brief The cube class inherits the drawable component and has convenience methods for generating cubes.
*/
class Cube : public Drawable {
  protected:
    void generateCube();
  public:
    Cube(AssetManager *am);
    ~Cube();
    void draw();
    void setTexture(Texture* text);
};

#endif
