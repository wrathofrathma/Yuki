#ifndef YUKI_HPP
#define YUKI_HPP

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <thread>

//Forward declaration before all of the includes.
class UI;
#include "AssetManager.hpp"
#include "GraphicsEngine.hpp"
#include "UserInput.hpp"
/**
\file Yuki.hpp
\brief Header file for Yuki.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 4/20/2019

*/


/**
\class Yuki
\brief The top level class of the game engine. It contains and directs IO between all other sub-classes and functions.
*/

class Yuki {
	private:
		//Handles any initialization we need, such as testing OpenGL versions, loading resources, etc.
		void init();
		void checkOpenGL();

		bool DEBUG;
		std::string program_title; ///< The title of our game.
		GLint opengl_major;
		GLint opengl_minor;

		inline static const std::string VERSION = "0.1"; ///< Version number

		bool running;

	public:
		Yuki(bool debug=false);
		~Yuki();
		bool isRunning();
		void close();
		AssetManager *am;	///< Pointer to our Asset Manager
		GraphicsEngine *ge;	///< Pointer to our Graphics Engine
		UI *ui; ///< Pointer to our input class.
};

#endif
