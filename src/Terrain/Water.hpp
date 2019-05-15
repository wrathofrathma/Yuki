#ifndef WATER_HPP
#define WATER_HPP
#include "../graphics/drawables/Quad.hpp"
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <cmath>

/**
\file Water.hpp
\brief Header file for Water.cpp

\author Christopher Arausa
\version Final
\date 05/14/2019
*/

/**
\class Water
\brief The water class handles our water quad
*/
class Water : public Quad {
  GLint gl_textures[3]; ///< Our individual texture for uv mapping
  float time;
  float dudv_offset; ///< Offset used for moving our distortion samples and getting a water ripple effect.
  public:
    Water();
    GLuint reflection_id; ///< Reflection textureID
    GLuint refraction_id; ///< Reflection textureID

    void draw(float delta, bool apply_distortion);
    Water(AssetManager *am);
};


#endif
