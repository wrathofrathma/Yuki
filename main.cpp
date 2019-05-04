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
	float m = 0.04;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			yu->ge->lights[0]->translate(glm::vec3(0,0,-m*2));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			yu->ge->lights[0]->translate(glm::vec3(-m*2,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			yu->ge->lights[0]->translate(glm::vec3(0,0,m*2));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			yu->ge->lights[0]->translate(glm::vec3(m*2,0,0));
		}
	}
	else{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			yu->ge->getCamera()->translate(glm::vec3(0,0,-m));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			yu->ge->getCamera()->translate(glm::vec3(-m,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			yu->ge->getCamera()->translate(glm::vec3(0,0,m));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			yu->ge->getCamera()->translate(glm::vec3(m,0,0));
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		yu->ge->getCamera()->rotate(glm::vec3(0,m,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		yu->ge->getCamera()->rotate(glm::vec3(0,-m,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		yu->ge->getCamera()->rotate(glm::vec3(m,0,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		yu->ge->getCamera()->rotate(glm::vec3(m,0,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		yu->ge->getCamera()->translate(glm::vec3(0,m,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
		yu->ge->getCamera()->translate(glm::vec3(0,-m,0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
		yu->ge->objects[0]->scale(glm::vec3(2.0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
		yu->ge->objects[0]->scale(glm::vec3(0.5, 0.5, 0.5));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
		yu->ge->lights[0]->setAmbient(yu->ge->lights[0]->getAmbient()-glm::vec4(0.01));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
		yu->ge->lights[0]->setAmbient(yu->ge->lights[0]->getAmbient()+glm::vec4(0.01));
	}
}

void setScene(Yuki &yu){
	Cube *cube = new Cube(yu.am);
	Quad *quad = new Quad(yu.am);
	quad->setTexture("doge");
	cube->scale(glm::vec3(3.0f));
	yu.ge->objects.push_back(cube);
	yu.ge->objects.push_back(quad);

	LightCube *light = new LightCube(yu.am);
//	light->scale(glm::vec3(0.2f));
	yu.ge->objects.push_back(light);

	yu.ge->lights.push_back(light);

}


int main(){
	Yuki yuki;
	yuki.ui->addKeyPressedEvent(keyPressedEvent);
	yuki.ui->addMouseMovedEvent(moveEvent);
	yuki.ui->addMouseButtonEvent(mouseButtonEvent);
	yuki.ui->addKeyStateProcessingEvent(stateProcessing);

	setScene(yuki);
	yuki.run();
	return 0;
}
