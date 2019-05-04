#include "Material.hpp"

Material::Material(glm::vec4 a, glm::vec4 d, glm::vec4 s, glm::vec4 e, float sh){
  ambient = a;
  diffuse = d;
  specular = s;
  emission = e;
  shininess = sh;
}

Material::~Material(){

}

glm::vec4 Material::getAmbient(){
  return ambient;
}

glm::vec4 Material::getDiffuse(){
  return diffuse;
}

glm::vec4 Material::getSpecular(){
  return specular;
}

glm::vec4 Material::getEmission(){
  return emission;
}

float Material::getShininess(){
  return shininess;
}

void Material::setAmbient(glm::vec4 a){
  ambient = a;
}

void Material::setDiffuse(glm::vec4 d){
  diffuse = d;
}

void Material::setSpecular(glm::vec4 s){
  specular = s;
}

void Material::setEmission(glm::vec4 e){
  emission = e;
}

void Material::setShininess(float sh){
  shininess = sh;
}
