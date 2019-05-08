#include "TestCube.hpp"
TestCube::TestCube(AssetManager *am){
  asset_manager = am;
  for(int i=0; i<6; i++){
    Quad* q = new Quad(am);
    q->setShader("Rotate");
    q->setMaterial(Materials::Default);
    faces.push_back(q);
  }
  faces[0]->translate(glm::vec3(0,0,-0.5));
  faces[1]->translate(glm::vec3(0,0,0.5));
  faces[2]->rotate(glm::vec3(0,deg*90,0));
  faces[2]->translate(glm::vec3(0,0.5,0),false);
  faces[3]->rotate(glm::vec3(0,deg*90,0));
  faces[3]->translate(glm::vec3(0,-0.5,0),false);
  faces[4]->rotate(glm::vec3(deg*90,0,0));
  faces[4]->translate(glm::vec3(0.5,0,0),false);
  faces[5]->rotate(glm::vec3(deg*90,0,0));
  faces[5]->translate(glm::vec3(-0.5,0,0),false);
}

TestCube::~TestCube(){
  for(int i=0; i<faces.size(); i++)
    delete faces[i];
}

void TestCube::draw(){
  for(Quad* q : faces){
    q->draw();
  }
}

void TestCube::setTexture(std::vector<Texture*> texts){
  if(texts.size() < 6)
    return;
  for(int i=0; i<6; i++){
    faces[i]->setTexture(texts[i]);
    faces[i]->setUseTexture(true);
  }
}
void TestCube::rotate(glm::vec3 rotation){
  for(Quad* q : faces){
    q->rotate(rotation);
  }
}

void TestCube::translate(glm::vec3 offset, bool relative){
  for(Quad* q : faces){
    q->translate(offset, relative);
  }
}

void TestCube::scale(glm::vec3 delta){
  for(Quad* q : faces){
    q->scale(delta);
  }
}
