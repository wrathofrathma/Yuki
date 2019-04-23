#include "UserInput.hpp"
#include "Yuki.hpp"

UI::UI(Yuki *yu){
	yuki=yu;
}
UI::~UI(){
	
}

//Our threaded input
void UI::processInput(){
	sf::Event event;
	while(yuki->ge->pollEvent(event)){
		if(event.type == sf::Event::Closed){
			yuki->close();
		}
		if(event.type == sf::Event::KeyPressed){
			for(void (*cb)(sf::Event::KeyEvent event, Yuki *yu) : keyPressedEvents){
				cb(event.key, yuki);
			}
		}
		else if(event.type == sf::Event::MouseMoved){
			for(void (*cb)(sf::Event::MouseMoveEvent event, Yuki *yu) : mouseMovedEvents)
			cb(event.mouseMove, yuki);
		}
		else if(event.type == sf::Event::MouseButtonPressed){
			for(void (*cb)(sf::Event::MouseButtonEvent event, Yuki *yu) : mouseButtonEvents){
				cb(event.mouseButton, yuki);
			}
		}
		else if(event.type == sf::Event::Resized){
			yuki->ge->resize();
		}
	}
	for(void (*cb)(Yuki *yu) : keyStateEvents){
		cb(yuki);
	}
}

void UI::addKeyPressedEvent(void (*callback)(sf::Event::KeyEvent event, Yuki *yu)){
	keyPressedEvents.push_back(callback);
}
void UI::addKeyStateProcessingEvent(void (*callback)(Yuki *yu)){
	keyStateEvents.push_back(callback);
}
void UI::addMouseButtonEvent(void (*callback)(sf::Event::MouseButtonEvent event, Yuki *yu)){
	mouseButtonEvents.push_back(callback);
}
void UI::addMouseMovedEvent(void (*callback)(sf::Event::MouseMoveEvent event, Yuki *yu)){
	mouseMovedEvents.push_back(callback);
}
