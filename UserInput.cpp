#include "UserInput.hpp"
#include "Yuki.hpp"

UI::UI(Yuki *yu){
	yuki=yu;
}
UI::~UI(){
	//If our thread is going, we need to end it and delete it.
	if(t_running){
		run_thread->join();
		delete run_thread;
	}
}

//Our threaded input
void UI::run(){
	GraphicsEngine *ge = yuki->ge;
	sf::Event event;
	while(ge->isOpen() && yuki->isRunning()){
		while(ge->pollEvent(event)){
			if(event.type == sf::Event::Closed){
				yuki->close();
			}
			if(event.type == sf::Event::KeyPressed){
				for(void (*cb)(sf::Event::KeyEvent event, Yuki *yu) : keyPressedEvents){
					cb(event.key, yuki);
				}
			}
		}
	}
}

void UI::start(){
	if(!t_running){
		run_thread = new std::thread(&UI::run, this);
		t_running = true;
	}
}
