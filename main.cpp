#include <iostream>
#include "src/Yuki.hpp"
#include "src/graphics/Scene.hpp"
#include "src/Graphics.hpp"
#include "src/UserInput.hpp"
#include <random>

#include "src/Assignment8/Assignment8.hpp"

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
		case sf::Keyboard::F10:
			yu->ge->screenshot();
			break;
		case sf::Keyboard::F11:
			{
			Scene* s = yu->getActiveScene();
			if(s!=nullptr)
				s->setActiveCamera("Sphere");
			}
			break;
		case sf::Keyboard::F12:
			{
			Scene* s = yu->getActiveScene();
			if(s!=nullptr)
				s->setActiveCamera("Free");
			}
			break;
	  default:
			break;
	};
}

void stateProcessing(Yuki *yu){
	float m = 0.04; //Move sensitivity.
	float r = 0.02; //Rotation sensitivity.

	Scene* scene = yu->getActiveScene();
	Camera* camera = scene->getCamera();

	if(camera->getType() == FREE){
		FreeCamera* c = (FreeCamera*)camera;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
			//Changes the roll.
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				if(camera->getType()==FREE)
					c->rotate(glm::vec3(0,0,r));
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				if(camera->getType()==FREE)
					c->rotate(glm::vec3(0,0,-r));
			}
		}
		else{
			//Camera translations
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				c->translate(glm::vec3(0,0,-m));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				c->translate(glm::vec3(-m,0,0));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				c->translate(glm::vec3(0,0,m));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				c->translate(glm::vec3(m,0,0));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				c->translate(glm::vec3(0,-m,0));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				c->translate(glm::vec3(0,m,0));
			}
			//Camera rotations
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				c->rotate(glm::vec3(0,-r,0));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				c->rotate(glm::vec3(0,r,0));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				c->rotate(glm::vec3(-r,0,0));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				c->rotate(glm::vec3(r,0,0));
			}
		}
	}
	else if(camera->getType()==SPHERICAL){
		SphericalCamera* c = (SphericalCamera*)camera;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
			//Changing camera radius
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				c->addR(-5*m);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				c->addR(5*m);
			}
		}
		else{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				c->addPsi(1);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				c->addPsi(-1);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				c->addTheta(1);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				c->addTheta(-1);
			}
		}
	}
}



int main(){
	Yuki yuki;
	yuki.ui->addKeyPressedEvent(keyPressedEvent);
	yuki.ui->addMouseMovedEvent(moveEvent);
	yuki.ui->addKeyStateEvent(stateProcessing);
	
	SchoolScene *ss = new SchoolScene(&yuki);

	yuki.addScene("school", ss);
	yuki.setActiveScene("school");
	yuki.run();
	return 0;
}
