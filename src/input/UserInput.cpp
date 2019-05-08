#include "UserInput.hpp"
#include "../Yuki.hpp"
#include "../graphics/GraphicsEngine.hpp"
#include "../graphics/Scene.hpp"

UI::UI(Yuki *yu){
	yuki=yu;
	mouseDown=false;
	setMouseSensitivity(sf::Vector2f(0.001f, 0.001f));
}
UI::~UI(){

}
void UI::setMouseDown(bool md){
	mouseDown = md;
}
bool UI::getMouseDown(){
	return mouseDown;
}

void UI::setMouseSensitivity(sf::Vector2f sensitivity){
	mouse_sensitivity = sensitivity;
}

sf::Vector2f UI::getMouseSensitivity(){
	return mouse_sensitivity;
}

//Our threaded input
void UI::processInput(Scene *scene){
	sf::Event event;
	while(yuki->ge->pollEvent(event)){
		if(event.type == sf::Event::Closed){
			yuki->close();
		}
		if(event.type == sf::Event::KeyPressed){
			for(void (*cb)(sf::Event::KeyEvent event, Yuki *yu) : keyPressedEvents){
				cb(event.key, yuki);
			}
			if(scene!=nullptr)
				scene->keyPressedEventHandler(event.key);
		}
		else if(event.type == sf::Event::MouseMoved){
			for(void (*cb)(sf::Event::MouseMoveEvent event, Yuki *yu) : mouseMovedEvents)
				cb(event.mouseMove, yuki);
			if(scene!=nullptr)
				scene->mouseMoveEventHandler(event.mouseMove);
		}
		else if(event.type == sf::Event::MouseButtonPressed){
			if(event.mouseButton.button == sf::Mouse::Left)
				mouseDown = true;
			for(void (*cb)(sf::Event::MouseButtonEvent event, Yuki *yu) : mouseButtonEvents){
				cb(event.mouseButton, yuki);
			}
			if(scene!=nullptr)
				scene->mouseButtonEventHandler(event.mouseButton);
		}
		else if(event.type == sf::Event::Resized){
			yuki->ge->resize();
		}
		else if(event.type == sf::Event::MouseButtonReleased){
			if(event.mouseButton.button == sf::Mouse::Left)
				mouseDown = false;
		}
	}
	for(void (*cb)(Yuki *yu) : keyStateEvents){
		cb(yuki);
	}
	if(scene!=nullptr)
		scene->keyStateEventHandler();
}

void UI::setMousePos(sf::Vector2i pos){
	last_mouse_pos = pos;
}
sf::Vector2i UI::getLastMousePos(){
	return last_mouse_pos;
}
void UI::addKeyPressedEvent(void (*callback)(sf::Event::KeyEvent event, Yuki *yu)){
	keyPressedEvents.push_back(callback);
}
void UI::addKeyStateEvent(void (*callback)(Yuki *yu)){
	keyStateEvents.push_back(callback);
}
void UI::addMouseButtonEvent(void (*callback)(sf::Event::MouseButtonEvent event, Yuki *yu)){
	mouseButtonEvents.push_back(callback);
}
void UI::addMouseMovedEvent(void (*callback)(sf::Event::MouseMoveEvent event, Yuki *yu)){
	mouseMovedEvents.push_back(callback);
}
