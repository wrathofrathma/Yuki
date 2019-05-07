#include "Light.hpp"

Light::Light(){
  setLight(on, glm::vec3(0.0), glm::vec3(0), glm::vec4(1), glm::vec4(1), glm::vec4(1));
}

Light::Light(bool onoff, glm::vec3 pos, glm::vec3 facing, glm::vec4 a, glm::vec4 d, glm::vec4 s){
  setLight(onoff, pos, facing, a, d, s);
}

Light::~Light(){

}


bool Light::getOn(){
  return on;
}

glm::vec4 Light::getAmbient(){
  return ambient;
}

glm::vec4 Light::getDiffuse(){
  return diffuse;
}

glm::vec4 Light::getSpecular(){
  return specular;
}

void Light::setOn(bool onoff){
  on = onoff;
}

void Light::setAmbient(glm::vec4 a){
  ambient = a;
}

void Light::setDiffuse(glm::vec4 d){
  diffuse = d;
}

void Light::setSpecular(glm::vec4 s){
  specular = s;
}


void Light::setLight(bool onoff, glm::vec3 pos, glm::vec3 facing, glm::vec4 a, glm::vec4 d, glm::vec4 s){
  on = onoff;
  position = pos;
  orientation = facing;
  ambient = a;
  diffuse = d;
  specular = s;
}
void Light::loadToShader(Shader *shader, unsigned int i){
  shader->bind();
  shader->setBool("light.on", on);
  glm::vec4 pos(position, 1.0);
  shader->setVec4("light.position", pos);
  shader->setVec4("light.ambient", ambient);
  shader->setVec4("light.diffuse", diffuse);
  shader->setVec4("light.specular", specular);
}
