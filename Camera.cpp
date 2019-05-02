#include "Camera.hpp"

Camera::Camera(GLuint uProj, GLuint uView, unsigned int width, unsigned int height, float FoV = 50.0f){
  this->uProj = uProj;
  this->uView = uView;
  this->width = width;
  this->height = height;
  this->FoV = FoV;
  camera_position = glm::vec3(0, 0, 2);
  YPR = glm::vec3(0,0,0);
  camera_up = glm::vec3(0, 1, 0);
  world_up = glm::vec3(0, 1, 0);
  camera_right = glm::vec3(1, 0, 0); //Don't actually need to specify this.
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
glm::mat4 Camera::getRotation(){
  return glm::mat4_cast(getRotationQ());
}

glm::quat Camera::getRotationQ(){
  //generate quaternions based on our Yaw Pitch and Roll
  glm::quat qyaw = glm::angleAxis(YPR.x, glm::vec3(0,1,0));
  glm::quat qpitch = glm::angleAxis(-YPR.y, glm::vec3(1,0,0));
  glm::quat qroll = glm::angleAxis(YPR.z, glm::vec3(0,0,1));
  //Generate the total accumulated rotation
  glm::quat orientation = qroll * qpitch * qyaw;
  //Normalize it/make it length 1
  return glm::normalize(orientation);
}
void Camera::updateView(){
  glm::mat4 rotation = getRotation();
  glm::mat4 translation = glm::mat4(1.0f);
  translation = glm::translate(translation,-camera_position);
  glm::mat4 view = rotation * translation;
  glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(view));
}


//Moves the camera in the direction of the offset.
void Camera::move(glm::vec3 offset){
  //Applying the offset to the camera position moves the camera
  moveForward(offset.z);
  moveRight(offset.x);
  moveUp(offset.y);
  //We also need to adjust our target by the same amount since we'd get some crane necking shit if we didn't.
}

glm::vec3 Camera::getForward(){
  glm::quat rotation = getRotationQ();
  return glm::conjugate(rotation) * glm::vec3(0, 0, 1);
}
glm::vec3 Camera::getRight(){
  glm::quat rotation = getRotationQ();
  return glm::conjugate(rotation) * glm::vec3(1, 0, 0);
}
glm::vec3 Camera::getUp(){
  glm::quat rotation = getRotationQ();
  return glm::conjugate(rotation) * glm::vec3(0, 1, 0);
}

void Camera::moveForward(float delta){
  camera_position+= getForward() * delta;
}
void Camera::moveRight(float delta){
  camera_position+= getRight() * delta;
}
void Camera::moveUp(float delta){
  camera_position+=getUp()*delta;
}
//Rotates the camera according to the degrees of rotation around each axis in the rotation vector
void Camera::rotate(glm::vec3 rotation){
  YPR += rotation;
}

void Camera::update(){
  updateProjection();
  updateView();
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
