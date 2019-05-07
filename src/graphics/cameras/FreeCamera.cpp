#include "FreeCamera.hpp"

FreeCamera::FreeCamera(unsigned int width, unsigned int height, float FoV = 50.0f) : Camera(width, height, FoV) {

  position = glm::vec3(0, 0, 2);
  orientation = glm::vec3(0,0,0);
  type = FREE;
  updateView();
}

FreeCamera::~FreeCamera(){

}

void FreeCamera::updateView(){
  glm::mat4 rotation = getRotationMatrix();
  glm::mat4 translation = glm::mat4(1.0f);
  translation = glm::translate(translation,-position);
  view = rotation * translation;
}

void FreeCamera::update(){
  updateView();
}
