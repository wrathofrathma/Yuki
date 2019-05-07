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
		if(yu->ge->getCamera()->getType()==FREE)
			((FreeCamera*)(yu->ge->getCamera()))->rotate(glm::vec3(-x,-y, 0));
		else{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				((SphericalCamera*)(yu->ge->getCamera()))->addR(delta_y*0.25);
			else{
				((SphericalCamera*)(yu->ge->getCamera()))->addTheta(delta_x*0.25);
				((SphericalCamera*)(yu->ge->getCamera()))->addPsi(delta_y*0.25);
			}
		}
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
		case sf::Keyboard::P:
			yu->ge->toggleCamera();
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->rotate(glm::vec3(0,0,-m));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->rotate(glm::vec3(0,0,m));
		}
	}
	else{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->translate(glm::vec3(0,0,-m));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->translate(glm::vec3(-m,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->translate(glm::vec3(0,0,m));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->translate(glm::vec3(m,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->translate(glm::vec3(0,m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->translate(glm::vec3(0,-m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->rotate(glm::vec3(0,-m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->rotate(glm::vec3(0,m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->rotate(glm::vec3(-m,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(yu->ge->getCamera()->getType()==FREE)
				((FreeCamera*)(yu->ge->getCamera()))->rotate(glm::vec3(m,0,0));
		}
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
				cube->setShader("CubeMap");
				cube->setPosition(glm::vec3(2*i,2*j,2*k));
				cube->setMaterial(Materials::Default);
				cube->setTexture(yu.am->getTexture("blue_space_box"));
				yu.ge->objects.push_back(cube);
			}
		}
	}

	Quad *plane = new Quad(yu.am);
	plane->setShader(yu.am->getShader("Rotate"));
	plane->setTexture("doge");
	plane->scale(glm::vec3(20.0f));
	plane->rotate(glm::vec3(0,1.57,0));
	plane->setMaterial(Materials::Default);
	yu.ge->objects.push_back(plane);

	Quad* wall1 = new Quad(yu.am);
	wall1->setShader("Rotate");
	wall1->setTexture("cat1");
	wall1->scale(glm::vec3(20.f));
	wall1->setPosition(glm::vec3(0,10,-20));
	wall1->setMaterial(Materials::Default);
	yu.ge->objects.push_back(wall1);

	LightCube *lc = new LightCube(yu.am);
	lc->setPosition(glm::vec3(0,10,-0));
	lc->setAmbient(glm::vec4(1));
	lc->setSpecular(glm::vec4(1));
	lc->setDiffuse(glm::vec4(0));
	lc->setOn(true);
	yu.ge->objects.push_back(lc);
	yu.ge->pLights.push_back(lc);
	Light* light = new Light(DIRECTIONAL);
	light->setAmbient(glm::vec4(0.1));
	light->setDiffuse(glm::vec4(0.3));
	light->setSpecular(glm::vec4(0.1));
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
