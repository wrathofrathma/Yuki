#include "SpacialObject.hpp"

SpacialObject::SpacialObject(){
  position = glm::vec3(0);
}
glm::vec3 SpacialObject::getPosition(){
  return position;
}
void SpacialObject::setPosition(glm::vec3 pos){
  position = pos;
}
void SpacialObject::setOrientation(glm::vec3 o){
  orientation = o;
}
glm::vec3 SpacialObject::getOrientation(){
  return orientation;
}
