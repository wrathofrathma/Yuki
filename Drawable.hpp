#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

/**
\file Drawable.hpp
\brief Header file for Drawable.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 4/20/2019

*/


/**
\class Drawable
\brief The Drawable class is the top level shell class representing anything that can be drawn onto our screen.
*/

class Drawable {

  public:
    Drawable();
    ~Drawable();
    virtual void draw() = 0;
};

#endif
