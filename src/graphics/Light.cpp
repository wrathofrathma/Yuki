#include "Light.hpp"

Light::Light(){
  setType(POINT);
  setOn(true);
  setPosition(glm::vec3(0));
  orientation = glm::vec3(0);
  setAmbient(glm::vec4(0.5));
  setDiffuse(glm::vec4(0.5));
  setSpecular(glm::vec4(0.5));
  constant = 1.0f;
  linear = 0.045f;
  quadratic = 0.0075f;
}
Light::Light(LIGHT_TYPE t){
  setType(t);
  setOn(true);
  setPosition(glm::vec3(0));
  orientation = glm::vec3(0);
  setAmbient(glm::vec4(0.5));
  setDiffuse(glm::vec4(0.5));
  setSpecular(glm::vec4(0.5));
  constant = 1.0f;
  linear = 0.045f;
  quadratic = 0.0075f;
}
//Directional constructor
Light::Light(bool onoff, glm::vec4 dir, glm::vec4 a, glm::vec4 d, glm::vec4 s){
  setType(DIRECTIONAL);
  setOn(onoff);
  orientation = dir;
  setAmbient(a);
  setDiffuse(d);
  setSpecular(s);
}
//Point constructor
Light::Light(bool onoff, glm::vec4 pos, glm::vec4 a, glm::vec4 d, glm::vec4 s, float c, float l, float q){
  setType(POINT);
  setOn(onoff);
  setPosition(pos);
  setAmbient(a);
  setDiffuse(d);
  setSpecular(s);
  setConstant(c);
  setLinear(l);
  setQuadratic(q);
}

//Generic
Light::Light(LIGHT_TYPE t, bool onoff, glm::vec4 a, glm::vec4 d, glm::vec4 s){
  setType(t);
  setOn(onoff);
  setAmbient(a);
  setDiffuse(d);
  setSpecular(s);
  if(t == POINT){
    constant = 1.0f;
    linear = 0.045f;
    quadratic = 0.0075f;
  }
  orientation = (glm::vec3(0));
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
void Light::setOff(Shader *s, unsigned int i, LIGHT_TYPE type){
  s->bind();
  std::string struct_pos="";
  switch(type){
    case POINT: {
      struct_pos+="pointLights[";
      struct_pos+=std::to_string(i);
      struct_pos+="].";
      s->setBool((struct_pos + "on"), false);
      }
      break;
    case DIRECTIONAL: {
      struct_pos+="directionalLights[";
      struct_pos+=std::to_string(i);
      struct_pos+="].";
      s->setBool((struct_pos + "on"), false);
      }
      break;
    case SPOT: {
      struct_pos+="spotLights[";
      struct_pos+=std::to_string(i);
      struct_pos+="].";
      s->setBool((struct_pos + "on"), false);
      }
      break;
  };
}

void Light::loadToShader(Shader *s, unsigned int i){
  s->bind();
  std::string struct_pos="";
  switch(type){
    case POINT: {
      struct_pos+="pointLights[";
      struct_pos+=std::to_string(i);
      struct_pos+="].";
      glm::vec4 pos(position, 1.0);
      s->setBool((struct_pos + "on"), on);
      s->setVec4((struct_pos + "position"),pos);
      s->setVec4((struct_pos + "ambient"), ambient);
      s->setVec4((struct_pos + "diffuse"), diffuse);
      s->setVec4((struct_pos + "specular"), specular);
      s->setFloat((struct_pos + "constant"), constant);
      s->setFloat((struct_pos + "linear"), linear);
      s->setFloat((struct_pos + "quadratic"), quadratic);
      }
      break;
    case DIRECTIONAL: {
      struct_pos+="directionalLights[";
      struct_pos+=std::to_string(i);
      struct_pos+="].";
      s->setBool((struct_pos + "on"), on);
      glm::vec4 dir(orientation,1);
      s->setVec4((struct_pos + "direction"), dir);
      s->setVec4((struct_pos + "ambient"), ambient);
      s->setVec4((struct_pos + "diffuse"), diffuse);
      s->setVec4((struct_pos + "specular"), specular);
      }
      break;
    case SPOT: {
      struct_pos+="spotLights[";
      struct_pos+=std::to_string(i);
      struct_pos+="].";
      glm::vec4 pos(position, 1.0);
      s->setBool((struct_pos + "on"), on);
      s->setVec4((struct_pos + "position"),pos);
      s->setVec4((struct_pos + "ambient"), ambient);
      s->setVec4((struct_pos + "diffuse"), diffuse);
      s->setVec4((struct_pos + "specular"), specular);
      s->setFloat((struct_pos + "constant"), constant);
      s->setFloat((struct_pos + "linear"), linear);
      s->setFloat((struct_pos + "quadratic"), quadratic);
      s->setFloat((struct_pos + "cutOff"), cutOff);
      s->setFloat((struct_pos + "outerCutOff"), outerCutOff);
      }
      break;
  };
}

float Light::getConstant(){
  return constant;
}

float Light::getLinear(){
  return linear;
}

float Light::getQuadratic(){
  return quadratic;
}

LIGHT_TYPE Light::getType(){
  return type;
}

void Light::setType(LIGHT_TYPE t){
  type = t;
}

void Light::setConstant(float c){
  constant = c;
}

void Light::setLinear(float l){
  linear = l;
}

void Light::setQuadratic(float q){
  quadratic = q;
}

void Light::setCutOff(float c){
  cutOff = c;
}

void Light::setOuterCutOff(float oc){
  outerCutOff = oc;
}

float Light::getCutOff(){
  return cutOff;
}

float Light::getOuterCutOff(){
  return outerCutOff;
}
