#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
/**
\file GraphicsEngine.hpp
\brief header file for GraphicsEngine.cpp

\author Christopher Arausa
\version 0.1
\date 4/20/2019

*/

/**
\class GraphicsEngine

\brief The Graphics class is an extension of sf::RenderWindow which manages our window and all of the graphics rendering.

*/

class GraphicsEngine : public sf::RenderWindow {
	private:
		bool resize_flag;
		int sscount;
	public:
		GraphicsEngine(std::string title="", GLint MajorVersion = 3, GLint MinorVersion = 3, int width=800, int height = 600);
		~GraphicsEngine();
		void setResizeFlag();
		void display();
		void screenshot();
		void resize();
		void setSize(unsigned int w, unsigned int h);
		void printOpenGLErrors();
};

#endif
