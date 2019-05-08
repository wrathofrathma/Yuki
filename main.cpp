#include <iostream>
#include "src/Yuki.hpp"
#include "src/graphics/Scene.hpp"
#include "src/Graphics.hpp"
#include "src/UserInput.hpp"
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
		if(yu->getActiveScene()->getCamera()->getType()==FREE)
			((FreeCamera*)(yu->getActiveScene()->getCamera()))->rotate(glm::vec3(-x,-y, 0));
		else{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				((SphericalCamera*)(yu->getActiveScene()->getCamera()))->addR(delta_y*0.25);
			else{
				((SphericalCamera*)(yu->getActiveScene()->getCamera()))->addTheta(delta_x*0.25);
				((SphericalCamera*)(yu->getActiveScene()->getCamera()))->addPsi(delta_y*0.25);
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
		case sf::Keyboard::O:
			yu->getActiveScene()->setActiveCamera("Sphere");
			break;
		case sf::Keyboard::P:
			yu->getActiveScene()->setActiveCamera("Free");
			break;
	  default:
			break;
	};
}
// void mouseButtonEvent(sf::Event::MouseButtonEvent event, Yuki *yu){
//
// }
//
//
void stateProcessing(Yuki *yu){
	float m = 0.04;
	Scene* scene = yu->getActiveScene();
	Camera* camera = scene->getCamera();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->rotate(glm::vec3(0,0,-m));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->rotate(glm::vec3(0,0,m));
		}
	}
	else{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->translate(glm::vec3(0,0,-m));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->translate(glm::vec3(-m,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->translate(glm::vec3(0,0,m));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->translate(glm::vec3(m,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->translate(glm::vec3(0,m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->translate(glm::vec3(0,-m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->rotate(glm::vec3(0,-m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->rotate(glm::vec3(0,m,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->rotate(glm::vec3(-m,0,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(camera->getType()==FREE)
				((FreeCamera*)camera)->rotate(glm::vec3(m,0,0));
		}
	}
}

void setSchoolScene(Yuki &yu){
	Scene* ss = new Scene(&yu);
	ss->addCamera("Free", new FreeCamera(yu.ge->getSize().x, yu.ge->getSize().y, 50.0f));
	ss->addCamera("Sphere", new SphericalCamera(yu.ge->getSize().x, yu.ge->getSize().y, 50.0f));
	ss->setActiveCamera("Free");

	ss->getCamera()->setPosition(glm::vec3(4,4,4));
	// std::vector<Texture*> texts;
	// texts.push_back(yu.am->getTexture("cat1"));
	// texts.push_back(yu.am->getTexture("cat2"));
	// texts.push_back(yu.am->getTexture("cat3"));
	// texts.push_back(yu.am->getTexture("doge"));
	// texts.push_back(yu.am->getTexture("doge"));
	// texts.push_back(yu.am->getTexture("doge"));
	// for(int i=2; i<6; i++){
	// 	for(int j=1; j<6; j++){
	// 		for(int k=2; k<6; k++){
	// 			TestCube* t = new TestCube(yu.am);
	// 			t->setTexture(texts);
	// 			t->translate(glm::vec3(2*i,2*j,2*k),false);
	// 			yu.ge->cubes.push_back(t);
	// 		}
	// 	}
	// }

	Quad *plane = new Quad(yu.am);
	plane->setShader(yu.am->getShader("Rotate"));
	plane->setTexture("doge");
	plane->scale(glm::vec3(20.0f));
	plane->rotate(glm::vec3(0,1.57,0));
	plane->setMaterial(Materials::Default);
	ss->addDrawables(plane);

	Quad* wall1 = new Quad(yu.am);
	wall1->setShader("Rotate");
	wall1->setTexture("cat1");
	wall1->scale(glm::vec3(20.f));
	wall1->setPosition(glm::vec3(0,10,-20));
	wall1->setMaterial(Materials::Default);
	ss->addDrawables(wall1);

	float a = 0.3;
	float d = 0.2;
	float s = 0.3;
	OrbitalLight* ol = new OrbitalLight();
	ol->setAmbient(glm::vec4(a));
	ol->setSpecular(glm::vec4(s));
	ol->setDiffuse(glm::vec4(d));
	ol->setPosition(50,45,45);
	ss->addLight(ol);
	OrbitalLight* ol1 = new OrbitalLight();
	ol1->setAmbient(glm::vec4(a));
	ol1->setSpecular(glm::vec4(s));
	ol1->setDiffuse(glm::vec4(d));
	ol1->setPosition(50,-45,100);
	ss->addLight(ol1);
	OrbitalLight* ol2 = new OrbitalLight();
	ol2->setAmbient(glm::vec4(a));
	ol2->setSpecular(glm::vec4(s));
	ol2->setDiffuse(glm::vec4(d));
	ol2->setPosition(50,-100,60);
	ss->addLight(ol2);
	ss->addMouseMovedEvent(moveEvent);
	ss->addKeyPressedEvent(keyPressedEvent);
	ss->addKeyStateEvent(stateProcessing);

	yu.addScene("school", ss);
	yu.setActiveScene("school");
}
// void setScene(Yuki &yu){
//
// 	LightCube *lc = new LightCube(yu.am);
// 	lc->setPosition(glm::vec3(6,6,4));
// 	lc->setAmbient(glm::vec4(1));
// 	lc->setSpecular(glm::vec4(1));
// 	lc->setDiffuse(glm::vec4(0.5));
// 	lc->scale(glm::vec3(1.1));
// 	lc->setOn(true);
// 	yu.ge->objects.push_back(lc);
// 	yu.ge->pLights.push_back(lc);
// 	Light* light = new Light(DIRECTIONAL);
// 	light->setAmbient(glm::vec4(0.1));
// 	light->setDiffuse(glm::vec4(0.3));
// 	light->setSpecular(glm::vec4(0.1));
// 	light->setOrientation(glm::vec3(-1,-1,-1));
// 	yu.ge->dLights.push_back(light);
// }


int main(){
	Yuki yuki;
	// yuki.ui->addKeyPressedEvent(keyPressedEvent);
	// yuki.ui->addMouseMovedEvent(moveEvent);
	// yuki.ui->addMouseButtonEvent(mouseButtonEvent);
	// yuki.ui->addKeyStateProcessingEvent(stateProcessing);

	setSchoolScene(yuki);
	yuki.run();
	return 0;
}
