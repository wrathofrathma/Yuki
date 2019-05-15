#include "LightCube.hpp"
/**
\file LightCube.cpp
\brief Implementation of the LightCube class.

\author    Christopher Arausa
\version   0.1
\date      05/8/2019

*/

/**
\brief Constructor

Sets the shader to a light shader and calls the cube superclass constructor.
\param am --- AssetManager pointer.
*/
LightCube::LightCube(AssetManager *am) : Cube(am) {
  setLightingOn(false);
  update = true;
}
/**
\brief Destructor

Default empty destructor.
*/
LightCube::~LightCube(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &dataPtr);
  glDeleteBuffers(1, &indicePtr);
}
