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
			yu->ge->pLights[0]->translate(glm::vec3(0,0,-m*2));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			yu->ge->pLights[0]->translate(glm::vec3(-m*2,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			yu->ge->pLights[0]->translate(glm::vec3(0,0,m*2));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			yu->ge->pLights[0]->translate(glm::vec3(m*2,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			yu->ge->pLights[0]->translate(glm::vec3(0,m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
			yu->ge->pLights[0]->translate(glm::vec3(0,-m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
			yu->ge->screenshot();
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			yu->ge->getCamera()->translate(glm::vec3(0,m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
			yu->ge->getCamera()->translate(glm::vec3(0,-m,0));
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

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
		yu->ge->objects[0]->scale(glm::vec3(2.0));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
		yu->ge->objects[0]->scale(glm::vec3(0.5, 0.5, 0.5));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
		yu->ge->pLights[0]->setAmbient(yu->ge->pLights[0]->getAmbient()-glm::vec4(0.01));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
		yu->ge->pLights[0]->setAmbient(yu->ge->pLights[0]->getAmbient()+glm::vec4(0.01));
	}
}

void setScene(Yuki &yu){
	yu.ge->getCamera()->setPosition(glm::vec3(4,4,4));
	for(int i=0; i<4; i++){
		for(int j=1; j<5; j++){
			for(int k=1; k<6; k++){
				Cube* cube = new Cube(yu.am);
				cube->setPosition(glm::vec3(2*i,2*j,2*k));
				cube->setMaterial(Materials::bluePlastic);
				yu.ge->objects.push_back(cube);
			}
		}
	}

	Quad *plane = new Quad(yu.am);
	plane->setTexture("doge");
	plane->scale(glm::vec3(20.0f));
	plane->rotate(glm::vec3(0,1.57,0));
	plane->setMaterial(Materials::Default);
	yu.ge->objects.push_back(plane);
	LightCube *lc = new LightCube(yu.am);
	lc->setPosition(glm::vec3(0,20,-0));
	lc->setAmbient(glm::vec4(1));
	lc->setSpecular(glm::vec4(1));
	lc->setDiffuse(glm::vec4(0));
	lc->setOn(true);
	yu.ge->objects.push_back(lc);
	yu.ge->pLights.push_back(lc);
	Light* light = new Light(DIRECTIONAL);
	light->setAmbient(glm::vec4(0.1));
	light->setDiffuse(glm::vec4(0.4));
	light->setSpecular(glm::vec4(0));
	light->setOrientation(glm::vec3(-1,-1,-1));
	yu.ge->dLights.push_back(light);
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
