#ifndef WATER_HPP
#define WATER_HPP
#include "../graphics/drawables/Quad.hpp"
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
class Water : public Quad {
  GLint gl_textures[3];

  public:
    Water();
    GLuint tex_id;
    void draw();
    Water(AssetManager *am);
};


#endif
