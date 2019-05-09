#include "Scene.hpp"
#include "../Yuki.hpp"
#include "cameras/Camera.hpp"
#include "components/Light.hpp"
#include "components/Drawable.hpp"
#include"../AssetManager.hpp"

/**
\file Scene.cpp
\brief Implementation of the Scene class.

\author    Christopher Arausa
\version   0.1
\date      05/8/2019

*/

/**
\brief Constructor

Default constructor that just stores our game engine pointer.
\param yuki --- Yuki class pointer.
*/
Scene::Scene(Yuki* yuki) {
  this->yuki = yuki;
  this->asset_manager = yuki->am;
  global_ambient = 0.1;
}

/**
\brief Destructor

Virtual destructor that cleans up any objects, cameras, and lighting in the scene.
*/
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

/**
\brief Calculates the delta time between updates, updates the camera matrices, and then calls virtual function update() which contains scene logic.

This is called every iteration in the primary game loop.
*/
void Scene::tick(){
  //Generate delta
  sf::Time curr_time = clock.getElapsedTime();
  sf::Time delta = curr_time - last_time;
  float dt = delta.asSeconds();
  last_time = curr_time;
  //Generate camera updates
  Camera *c = getCamera();
  if(c!=nullptr)
    c->update();
  update(dt);
}

/**
\brief Virtual update function called from tick() every game loop.
\param delta --- Delta time between update calls.
*/
void Scene::update(float delta){
    //Default update function does nothing.
}
/**
\brief Virtual draw function for drawing the scene.

By default we just draw all drawable objects. This is probably going to change in the future when we have more complex needs.
*/
void Scene::draw(){
  for(Drawable* d : drawables)
    d->draw();
}

/**
\brief Adds a camera to the scene.

If a camera of the id already exists, it overwrites that camera.
\param id --- Key to store the camera in our map under.
\param c --- Camera pointer of the camera to store.
*/
void Scene::addCamera(std::string id, Camera* c){
  if(cameras.count(id)>0){
    std::cerr << "Camera ID already exists. Overwriting old camera" << std::endl;
    removeCamera(id);
  }
  cameras.insert(std::pair<std::string,Camera*>(id,c));
}
/**
\brief Removes a camera from the scene.
\param id --- Camera ID to remove.
*/
void Scene::removeCamera(std::string id){
  if(cameras.size()==0)
		return;
	if(cameras.count(id)==0)
		return;
	//The actual deletion
  if(cameras[id]!=nullptr){
	 delete cameras[id];
   cameras[id] = nullptr;
  }
	cameras.erase(id);
	//If our deleted camera was our active camera, then we should pick the camera at the bottom of the map. If one doesn't exist then we just set to "".
	if(active_camera.compare(id)==0){
		if(cameras.size()>0)
			active_camera = cameras.begin()->first;
		else
			active_camera.clear();
	}
}
/**
\brief Sets the active camera in the scene.
\param id --- ID of the camera to set as active.
*/
void Scene::setActiveCamera(std::string id){
  if(cameras.count(id)==0){
    std::cerr << "Couldn't set active camera. ID not found." << std::endl;
    return;
  }
  active_camera = id;
}
/**
\brief Returns the active camera of the scene.
*/
Camera* Scene::getCamera(){
  if(cameras.size()==0 || active_camera.size()==0 || cameras.count(active_camera)==0){
    std::cerr << "Couldn't find active camera." << std::endl;
    return nullptr;
  }
	return cameras[active_camera];
}
/**
\brief Adds a light to the scene.

This is probably going to be switched out later when we have more complex needs.
\param l --- Light pointer to add to the scene.
*/
void Scene::addLight(Light* l){
  lights.push_back(l);
}

/**
\brief Adds a drawable object to the scene.

This will definitely be switched out later or removed when we have more complex scene logic.
\param d --- Drawable pointer to add to our list of things to draw.
*/
void Scene::addDrawables(Drawable* d){
  drawables.push_back(d);
}
/**
\brief Returns the vector of all lights in the scene.
*/
std::vector<Light*> Scene::getLights(){
  return lights;
}
/**
\brief Returns all of the drawable objects in the scene.
*/
std::vector<Drawable*> Scene::getDrawables(){
  return drawables;
}
/**
\brief Sets the global ambient lighting value of the scene.
*/
void Scene::setGlobalAmbient(float a){
  global_ambient = a;
}
/**
\brief Returns the global ambient lighting value of the scene.
*/
float Scene::getGlobalAmbient(){
  return global_ambient;
}
/**
\brief Virtual function for scene key event logic.
*/
void Scene::keyPressedEventHandler(sf::Event::KeyEvent event){

}
/**
\brief Virtual function for scene key state logic.
*/
void Scene::keyStateEventHandler(){

}
/**
\brief Virtual function for scene mouse button logic.
*/
void Scene::mouseButtonEventHandler(sf::Event::MouseButtonEvent event){

}
/**
\brief Virtual function for scene mouse move logic.
*/
void Scene::mouseMoveEventHandler(sf::Event::MouseMoveEvent event){

}
