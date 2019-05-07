#include "QuaternionObject.hpp"

QuaternionObject::QuaternionObject(){
  position = glm::vec3(0);
  orientation = glm::vec3(0);
  current_scale = glm::vec3(1.0f);
  model_matrix = glm::mat4(1.0f);
}
QuaternionObject::~QuaternionObject(){

}

void QuaternionObject::rotate(glm::vec3 rotation){
  orientation+=rotation;
}

glm::mat4 QuaternionObject::getRotationMatrix(){
  return glm::mat4_cast(getRotationQuat());
}

glm::quat QuaternionObject::getRotationQuat(){
  //generate quaternions based on our Yaw Pitch and Roll
  glm::quat qyaw = glm::angleAxis(orientation.x, glm::vec3(0,1,0));
  glm::quat qpitch = glm::angleAxis(orientation.y, glm::vec3(1,0,0));
  glm::quat qroll = glm::angleAxis(orientation.z, glm::vec3(0,0,1));
  //Generate the total accumulated rotation
  glm::quat orientation = qroll * qpitch * qyaw;
  //Normalize it/make it length 1
  return glm::normalize(orientation);
}

glm::vec3 QuaternionObject::getXAxis(){
  glm::quat rotation = getRotationQuat();
  return glm::conjugate(rotation) * glm::vec3(1, 0, 0);
}
void QuaternionObject::setOrientation(glm::vec3 o){
  orientation = o;
}

glm::vec3 QuaternionObject::getYAxis(){
  glm::quat rotation = getRotationQuat();
  return glm::conjugate(rotation) * glm::vec3(0, 1, 0);
}

glm::vec3 QuaternionObject::getZAxis(){
  glm::quat rotation = getRotationQuat();
  return glm::conjugate(rotation) * glm::vec3(0, 0, 1);
}

void QuaternionObject::translate(glm::vec3 offset, bool relative){
  if(relative){
    position+=getXAxis() * offset.x;
    position+=getYAxis() * offset.y;
    position+=getZAxis() * offset.z;
  }
  else{
    position+=offset;
  }
}
void QuaternionObject::setPosition(glm::vec3 pos){
  position = pos;
}
glm::vec3 QuaternionObject::getPosition(){
  return position;
}

glm::mat4 QuaternionObject::generateModelMatrix(){
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
  glm::mat4 rotationMatrix = getRotationMatrix();
  glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), current_scale);
  model_matrix = translationMatrix * rotationMatrix * scaleMatrix;
  return model_matrix;
}

void QuaternionObject::scale(glm::vec3 delta){
  current_scale*=delta;
}

glm::vec3 QuaternionObject::getOrientation(){
  return orientation;
}
