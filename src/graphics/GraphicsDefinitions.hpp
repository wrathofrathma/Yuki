#ifndef GRAPHICS_DEFINITIONS_HPP
#define GRAPHICS_DEFINITIONS_HPP
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
/**
\file GraphicsDefinitions.hpp
\brief Basic material properties for normal surfaces, texture struct, vertex struct, and some other miscelleneous definitions.

\author Christopher Arausa
\version 0.1
\date 4/27/2019
*/

#define BUFFER_OFFSET(x) ((const void*) (x))
#define PI 3.14159265358979323846264338328
#define PI_DIV_180 0.0174532925199432957692369076849
#define deg PI_DIV_180

void printOpenGLErrors();

#endif
