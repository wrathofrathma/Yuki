#include "Camera.hpp"

Camera::Camera(unsigned int width, unsigned int height, float FoV = 50.0f){
  this->width = width;
  this->height = height;
  this->FoV = FoV;


  clip_near = 0.1f;
  clip_far = 100.0f;

  updateProjection();
}

Camera::~Camera(){

}
void Camera::resize(unsigned int width, unsigned int height){
  this->width = width;
  this->height = height;
  updateProjection();
}
void Camera::updateProjection(){
  projection = glm::perspective(glm::radians(FoV), float(width) / float(height), clip_near, clip_far);
}


glm::mat4 Camera::getView(){
  return view;
}

glm::mat4 Camera::getProjection(){
  return projection;
}
CAMERA_TYPE Camera::getType(){
  return type;
}
void Camera::applyUpdate(Shader *shader){
  shader->bind();
  shader->setMat4(shader->getUniformLocation(VIEW), view);
  shader->setMat4(shader->getUniformLocation(PROJECTION), projection);
  shader->setVec3(shader->getUniformLocation("camera_pos"),position);
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
