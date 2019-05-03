#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Drawable.hpp"
#include "GraphicsDefinitions.hpp"
#include "Camera.hpp"
#include "drawables/Quad.hpp"
#include "drawables/Cube.hpp"
class Yuki;

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
		Quad *quad;
		Cube *cube;
		bool wireframe;
		Yuki *yuki;
		std::map<std::string, Camera*> cameras;
		std::string active_camera;
	public:
		GraphicsEngine(Yuki* yu, std::string title="", GLint MajorVersion = 3, GLint MinorVersion = 3, int width=800, int height = 600);
		~GraphicsEngine();
		void setResizeFlag();
		void display();
		void screenshot();
		void resize();
		void setSize(unsigned int w, unsigned int h);
		void toggleWireframe();
		bool getWireframe();
		void setWireframe(bool v);
		void setActiveCamera(std::string c);
		Camera* getCamera();
};

#endif
