#include "Camera.hpp"

Camera::Camera(GLuint uProj, GLuint uView, unsigned int width, unsigned int height, float FoV = 50.0f){
  this->uProj = uProj;
  this->uView = uView;
  this->width = width;
  this->height = height;
  this->FoV = FoV;
  camera_position = glm::vec3(2, 2, 2);
  camera_up = glm::vec3(0, 1, 0);
  clip_near = 0.1f;
  clip_far = 100.0f;
  updateProjection();
  updateView();
}

Camera::~Camera(){

}
void Camera::resize(unsigned int width, unsigned int height){
  this->width = width;
  this->height = height;
  updateProjection();
}
void Camera::updateProjection(){
  glm::mat4 projection = glm::perspective(glm::radians(FoV), float(width) / float(height), clip_near, clip_far);
  glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::updateView(){
  glm::mat4 view = glm::lookAt(camera_position, camera_position, camera_up);
  glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::update(){

  //Calculate camera face based on current angles

}

void Camera::setPosition(glm::vec3 pos){
  camera_position = pos;
  updateView();
}


void Camera::setFOV(float fov){
  FoV = fov;
  updateProjection();
}

void Camera::setClipping(float near, float far){
  clip_near = near;
  clip_far = far;
  updateProjection();
}
