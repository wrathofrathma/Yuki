#ifndef USER_INPUT_HPP
#define USER_INPUT_HPP
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
//Forward declaration for later.
class Yuki;
/**
\file UserInput.hpp
\brief Header file for UserInput.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 4/20/2019

*/


/**
\class UI
\brief The UI class handles user input.
*/

class UI {
	private:
		sf::Vector2i last_position; ///< Last position of the mouse on screen.
		Yuki* yuki; ///< Our link back up to the rest of our resources.

		std::vector<void (*)(sf::Event::KeyEvent event, Yuki *yu)> keyPressedEvents;
		std::vector<void (*)(Yuki *yu)> keyStateEvents;
		std::vector<void (*)(sf::Event::MouseButtonEvent event, Yuki *yu)> mouseButtonEvents;
		std::vector<void (*)(sf::Event::MouseMoveEvent event, Yuki *yu)> mouseMovedEvents;

	public:
		UI(Yuki *yu);
		~UI();

		void processInput();

		//Adding things to our input-event loop check.
		void addKeyPressedEvent(void (*callback)(sf::Event::KeyEvent event, Yuki *yu));
		void addKeyStateProcessingEvent(void (*callback)(Yuki *yu));
		void addMouseButtonEvent(void (*callback)(sf::Event::MouseButtonEvent event, Yuki *yu));
		void addMouseMovedEvent(void (*callback)(sf::Event::MouseMoveEvent event, Yuki *yu));
};

#endif
