#include <iostream>
#include "src/Yuki.hpp"
#include "src/graphics/Scene.hpp"
#include "src/Graphics.hpp"
#include "src/UserInput.hpp"
#include <ctime>
#include <cstdlib>

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

// void schoolUpdate(Yuki* yu, Scene* scene, float delta){
// 	yu->am->getShader("Rotate")->setFloat("time", scene->clock.getElapsedTime().asSeconds()/2.0);
// 	for(Drawable* d : scene->getDrawables()){
// 		d->rotate(glm::vec3())
// 	}
// }

class SchoolScene : public Scene {
	private:
		std::vector<TestCube*> cubes;
  public:
		SchoolScene(Yuki *yuki) : Scene(yuki) {
			//Well first off we have two cameras.
			setGlobalAmbient(0.3);
			addCamera("Free", new FreeCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
			addCamera("Sphere", new SphericalCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
			setActiveCamera("Free");
			getCamera()->setPosition(glm::vec3(0,10,-10));
			((FreeCamera *)getCamera())->rotate(glm::vec3(2.7,0,0));
			//We have roughly 50 face cubes.
			std::vector<Texture*> texts;
			texts.push_back(asset_manager->getTexture("cat1"));
			texts.push_back(asset_manager->getTexture("cat2"));
			texts.push_back(asset_manager->getTexture("cat3"));
			texts.push_back(asset_manager->getTexture("doge"));
			texts.push_back(asset_manager->getTexture("doge"));
			texts.push_back(asset_manager->getTexture("doge"));
			for(int i=2; i<6; i++){
				for(int j=1; j<11; j++){
					for(int k=1; k<6; k++){
						TestCube* t = new TestCube(asset_manager);
						t->setTexture(texts);
						t->translate(glm::vec3(2*i,2*j,2*k),false);
						t->setMaterial(Materials::Default);
						cubes.push_back(t);
					}
				}
			}
			//We also have a flat ground plane.
			Quad *plane = new Quad(asset_manager);
			plane->setTexture("stone");
			plane->scale(glm::vec3(20.0f));
			plane->rotate(glm::vec3(0,1.57,0));
			plane->setMaterial(Materials::greenTint);
			addDrawables(plane);

			//I like having a wall of rotating cats.
			Quad* wall1 = new Quad(asset_manager);
			wall1->setShader("Rotate");
			wall1->setTexture("cat1");
			wall1->scale(glm::vec3(20.f));
			wall1->setPosition(glm::vec3(0,10,-20));
			wall1->setMaterial(Materials::Default);
			addDrawables(wall1);

			//Lighting replicating similar variables to what was provided.
			float a = 0.3;
			float d = 0.2;
			float s = 0.3;
			OrbitalLight* ol = new OrbitalLight();
			ol->setAmbient(glm::vec4(a));
			ol->setSpecular(glm::vec4(s));
			ol->setDiffuse(glm::vec4(d));
			ol->setPosition(50,45,45);
			addLight(ol);
			OrbitalLight* ol1 = new OrbitalLight();
			ol1->setAmbient(glm::vec4(a));
			ol1->setSpecular(glm::vec4(s));
			ol1->setDiffuse(glm::vec4(d));
			ol1->setPosition(50,-45,100);
			addLight(ol1);
			OrbitalLight* ol2 = new OrbitalLight();
			ol2->setAmbient(glm::vec4(a));
			ol2->setSpecular(glm::vec4(s));
			ol2->setDiffuse(glm::vec4(d));
			ol2->setPosition(50,-100,60);
			addLight(ol2);

			cube_rotate = false;
			text_rotate = false;
		}
		~SchoolScene(){
			while(cameras.size()>0){
				std::map<std::string, Camera*>::iterator it = cameras.begin();
				if(it->second!=nullptr){
					delete it->second;
					it->second = nullptr;
				}
				cameras.erase(it);
			}
			for(unsigned int i=0; i<lights.size(); i++){
				if(lights[i]!=nullptr){
					delete lights[i];
					lights[i]=nullptr;
				}
			}
			for(unsigned int i=0; i<drawables.size(); i++){
				if(drawables[i]!=nullptr){
					delete drawables[i];
					drawables[i]=nullptr;
				}
			}
			for(unsigned int i=0; i<cubes.size(); i++){
				if(cubes[i]!=nullptr){
					delete cubes[i];
					cubes[i]=nullptr;
				}
			}
		}

		bool text_rotate;
		bool cube_rotate;
		glm::vec3 rot_vector;
		float rot_speed = 0.05;

    void update(float delta){
			if(text_rotate)
				asset_manager->getShader("Rotate")->setFloat("time",clock.getElapsedTime().asSeconds()/2.0);
			if(cube_rotate){
				for(TestCube* c : cubes){
					c->rotate();
				}
			}
		}
    //Scene draw function.
    void draw(){
			for(Drawable* d : drawables)
				d->draw();

			for(TestCube* c : cubes)
				c->draw();
		}
    //Functions that will determine how our scene handles input.
    void keyPressedEventHandler(sf::Event::KeyEvent event){
			switch(event.code){
				case sf::Keyboard::T:
					if(text_rotate==false)
						text_rotate = true;
					else
						text_rotate = false;
					break;
				case sf::Keyboard::R: {
					if(cube_rotate==true){
						for(TestCube *c : cubes)
							c->setRotateVector(glm::vec3(0));
							cube_rotate=false;
						}
					else {
						cube_rotate = true;
						srand(time(nullptr));
						for(TestCube *c : cubes){
							rot_vector.x = (rand()% 100)/1000.0;
							rot_vector.y = (rand()% 100)/1000.0;
							rot_vector.z = (rand()% 100)/1000.0;
							c->setRotateVector(rot_vector);
						}
					}
					}
					break;
				case sf::Keyboard::F1:
					//Toggle ground lights on
					drawables[0]->setLightingOn(true);
					break;
				case sf::Keyboard::F2:
					//Toggle ground lights off
					drawables[0]->setLightingOn(false);
					break;
				case sf::Keyboard::F3:
					//Toggle ground texture on
					drawables[0]->setUseTexture(true);
					break;
				case sf::Keyboard::F4:
					//toggle ground texture off.
					drawables[0]->setUseTexture(false);
					break;
				case sf::Keyboard::F5:
					//Turn on cube lights
					for(TestCube *c : cubes){
						c->setLightingOn(true);
					}
					break;
				case sf::Keyboard::F6:
					//turn off cube lights
					for(TestCube *c : cubes){
						c->setLightingOn(false);
					}
					break;
				case sf::Keyboard::F7:
					//Turn on cube texture.
					for(TestCube* c : cubes){
						c->setUseTexture(true);
					}
					break;
				case sf::Keyboard::F8:
					//Turn off cube textures.
					for(TestCube* c : cubes){
						c->setUseTexture(false);
					}
					break;
				default:
					break;
			};
		}
    void keyStateEventHandler(){}
    void mouseButtonEventHandler(sf::Event::MouseButtonEvent event){}
    void mouseMoveEventHandler(sf::Event::MouseMoveEvent event){}
};

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
