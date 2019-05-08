#include "Scene.hpp"
#include "../Yuki.hpp"
#include "cameras/Camera.hpp"
#include "components/Light.hpp"
#include "components/Drawable.hpp"

Scene::Scene(Yuki* yuki) : UI(yuki){

}

Scene::~Scene(){
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
}
void Scene::draw(){

}
void Scene::addCamera(std::string s, Camera* c){
  if(cameras.count(s)>0){
    std::cerr << "Camera ID already exists. Overwriting old camera" << std::endl;
    removeCamera(s);
  }
  cameras.insert(std::pair<std::string,Camera*>(s,c));
}

void Scene::removeCamera(std::string s){
  if(cameras.size()==0)
		return;
	if(cameras.count(s)==0)
		return;
	//The actual deletion
  if(cameras[s]!=nullptr){
	 delete cameras[s];
   cameras[s] = nullptr;
  }
	cameras.erase(s);
	//If our deleted camera was our active camera, then we should pick the camera at the bottom of the map. If one doesn't exist then we just set to "".
	if(active_camera.compare(s)==0){
		if(cameras.size()>0)
			active_camera = cameras.begin()->first;
		else
			active_camera.clear();
	}
}
void Scene::setActiveCamera(std::string s){
  if(cameras.count(s)>0){
    std::cerr << "Couldn't set active camera. ID not found." << std::endl;
    return;
  }
  active_camera = s;
}

Camera* Scene::getCamera(){
  if(cameras.size()==0 || active_camera.size()==0 || cameras.count(active_camera)==0){
    std::cerr << "Couldn't find active camera." << std::endl;
    return nullptr;
  }
	return cameras[active_camera];
}

void Scene::update(){
  //Generate delta
  sf::Time curr_time = clock.getElapsedTime();
  sf::Time delta = curr_time - last_time;
  float dt = delta.asSeconds();
  last_time = curr_time;

  //Generate camera updates
  Camera *c = getCamera();
  if(c!=nullptr)
    c->update();
  for(void (*cb)(Yuki *yu, Scene* scene, float delta) : update_events)
    cb(yuki, this, dt);
}

void Scene::addLight(Light* l){
  lights.push_back(l);
}

void Scene::addDrawables(Drawable* d){
  drawables.push_back(d);
}

std::vector<Light*> Scene::getLights(){
  return lights;
}

std::vector<Drawable*> Scene::getDrawables(){
  return drawables;
}

void Scene::setGlobalAmbient(float a){
  global_ambient = a;
}

float Scene::getGlobalAmbient(){
  return global_ambient;
}
