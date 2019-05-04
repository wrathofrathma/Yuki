#include <iostream>
#include "src/Yuki.hpp"

//This file is effectively our "Game" or test file. Everything else is done in the game engine. 

using namespace std;


void moveEvent(sf::Event::MouseMoveEvent event, Yuki *yu){
	UI *ui = yu->ui;
	sf::Vector2i last_pos = ui->getLastMousePos();
	sf::Vector2f mouse_sensitivity = ui->getMouseSensitivity();

	if(ui->getMouseDown()){
		float delta_x = event.x - last_pos.x;
		float delta_y = event.y - last_pos.y;
		float x = delta_x * mouse_sensitivity.x;
		float y = delta_y * mouse_sensitivity.y;
		yu->ge->getCamera()->rotate(glm::vec3(-x,-y, 0));
	}
	ui->setMousePos(sf::Vector2i(event.x, event.y));
}
void keyPressedEvent(sf::Event::KeyEvent event, Yuki *yu){
	switch(event.code){

		case sf::Keyboard::Escape:
			yu->close();
			break;
		case sf::Keyboard::M:
			yu->ge->toggleWireframe();
			break;
	  default:
			break;
	};
}
void mouseButtonEvent(sf::Event::MouseButtonEvent event, Yuki *yu){

}


void stateProcessing(Yuki *yu){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		yu->ge->getCamera()->translate(glm::vec3(0,0,-0.03));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		yu->ge->getCamera()->translate(glm::vec3(-0.03,0,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		yu->ge->getCamera()->translate(glm::vec3(0,0,0.03));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		yu->ge->getCamera()->translate(glm::vec3(0.03,0,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		yu->ge->getCamera()->rotate(glm::vec3(0,0.03,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		yu->ge->getCamera()->rotate(glm::vec3(0,-0.03,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		yu->ge->getCamera()->rotate(glm::vec3(-0.03,0,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		yu->ge->getCamera()->rotate(glm::vec3(0.03,0,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		yu->ge->getCamera()->translate(glm::vec3(0,0.03,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
		yu->ge->getCamera()->translate(glm::vec3(0,-0.03,0));
	}
}

int main(){
	Yuki yuki;
	yuki.ui->addKeyPressedEvent(keyPressedEvent);
	yuki.ui->addMouseMovedEvent(moveEvent);
	yuki.ui->addMouseButtonEvent(mouseButtonEvent);
	yuki.ui->addKeyStateProcessingEvent(stateProcessing);

	yuki.run();
	return 0;
}
