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
    bool skybox; ///< Boolean for whether this cube is a skybox. This means we're going to cut the translation out of the view matrix.
  public:
    Cube(AssetManager *am);
    void setSkybox(bool sb);
    bool isSkybox();
    ~Cube();
    void draw();
    void setTexture(Texture* text);
};

#endif
