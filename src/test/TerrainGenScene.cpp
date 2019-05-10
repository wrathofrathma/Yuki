#include "../graphics/components/Light.hpp"
#include "../graphics/lights/OrbitalLight.hpp"
#include "../graphics/drawables/Cube.hpp"
#include "../graphics/cameras/Camera.hpp"
#include "../Yuki.hpp"
#include "../Terrain/TerrainChunk.hpp"
#include "../graphics/cameras/FreeCamera.hpp"
#include "../graphics/cameras/SphericalCamera.hpp"
#include "../Graphics.hpp"
#include "../graphics/drawables/Mesh.hpp"
#include <chrono>

#include "TerrainGenScene.hpp"

TGenScene::TGenScene(Yuki *yuki) : Scene(yuki){
  setGlobalAmbient(glm::vec4(0.8));
  addCamera("Free", new FreeCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
  addCamera("Sphere", new SphericalCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
  setActiveCamera("Free");
  getCamera()->setPosition(glm::vec3(4000,10,4000));
  ((FreeCamera*)getCamera())->rotate(glm::vec3(3.2,0,0));
  skybox = new Cube(yuki->am);
  skybox->setTexture(yuki->am->getTexture("totality"));
  skybox->setLightingOn(false);
  skybox->setMaterial(Materials::Default);
  skybox->scale(glm::vec3(250));
  skybox->setSkybox(true);

  float a = 0.3;
  float d = 0.2;
  float s = 0.3;
  OrbitalLight* ol = new OrbitalLight();
  ol->setAmbient(glm::vec4(a));
  ol->setSpecular(glm::vec4(s));
  ol->setDiffuse(glm::vec4(d));
  ol->setPosition(50,45,45);
  OrbitalLight* ol1 = new OrbitalLight();
  ol1->setAmbient(glm::vec4(a));
  ol1->setSpecular(glm::vec4(s));
  ol1->setDiffuse(glm::vec4(d));
  ol1->setPosition(50,-45,100);
  OrbitalLight* ol2 = new OrbitalLight();
  ol2->setAmbient(glm::vec4(a));
  ol2->setSpecular(glm::vec4(s));
  ol2->setDiffuse(glm::vec4(d));
  ol2->setPosition(50,-100,60);
  lights.push_back(ol);
  lights.push_back(ol1);
  lights.push_back(ol2);

  seed = std::chrono::system_clock::now().time_since_epoch().count();
  chunk_size = 32;
}

TGenScene::~TGenScene(){
  clearCameras();
  for(unsigned int i=0; i<lights.size(); i++){
    if(lights[i]!=nullptr){
      delete lights[i];
      lights[i]=nullptr;
    }
  }
  delete skybox;


}

void TGenScene::draw(){
  skybox->draw();

  for(auto const& [key, val] : chunks) {
    val->draw();
  }

}


void TGenScene::update(float delta){
  int viewDis = 128/chunk_size;
  //Camera position
  glm::vec3 cpos = getCamera()->getPosition();
  //Converted to chunk coordinates.
  int x = cpos.x/chunk_size;
  int z = cpos.z/chunk_size;
  //Generate range to check
  int lower_x = x-viewDis;
  int lower_z = z-viewDis;
  int upper_x = x+viewDis;
  int upper_z = z+viewDis;
  //Check all chunks that should be within our view.
  for(int i=lower_x; i<upper_x; i++){
    for(int j=lower_z; j<upper_z; j++){
      //Our pair key
      std::pair<int,int> p = std::make_pair(i,j);
      //If the chunk doesn't exist let's make it
      if(chunks.count(p)==0){
        chunks.insert(std::make_pair(p,new TerrainChunk(asset_manager, i, j,seed, chunk_size,chunk_size)));
      }
    }
  }
}

void TGenScene::updateShaders(){
  Camera* camera = getCamera();
  for(auto const& [key, val] : yuki->am->getShaders()) {
    if(camera!=nullptr){
      camera->applyUpdate(val);
    }
    glm::vec4 a = getGlobalAmbient();
    val->setVec4("global_ambient", a);
    unsigned int ds = 0;
    unsigned int ss = 0;
    unsigned int ps = 0;
    for(unsigned int i=0; i<lights.size(); i++){
      switch(lights[i]->getType()){
        case POINT:
          lights[i]->loadToShader(val,ps);
          ps++;
          break;
        case SPOT:
          lights[i]->loadToShader(val,ss);
          ss++;
          break;
        case DIRECTIONAL:
          lights[i]->loadToShader(val,ds);
          ds++;
        break;
      };
    }
  }
}

void TGenScene::keyPressedEventHandler(sf::Event::KeyEvent event){

}

void TGenScene::keyStateEventHandler(){

}

void TGenScene::mouseButtonEventHandler(sf::Event::MouseButtonEvent event){

}

void TGenScene::mouseMoveEventHandler(sf::Event::MouseMoveEvent event){

}
