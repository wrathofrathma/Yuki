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
#include "../graphics/ObjModel.hpp"
#include "TerrainGenScene.hpp"
#include "../graphics/components/Light.hpp"

TGenScene::TGenScene(Yuki *yuki) : Scene(yuki){
  setGlobalAmbient(glm::vec4(0.1));
  draw_mesh = false;
  draw_skybox = true;
  addCamera("Free", new FreeCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
  addCamera("Sphere", new SphericalCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
  setActiveCamera("Free");
  skybox = nullptr;
  getCamera()->setPosition(glm::vec3(4000,10,4000));
  //((FreeCamera*)getCamera())->rotate(glm::vec3(3.2,0,0));


  // light->setPosition(glm::vec3(0));
  //light->setConstant(1);
  // light->setAmbient(glm::vec4(0.1));
  // light->setSpecular(glm::vec4(0.4));
  // light->setDiffuse(glm::vec4(138/255.0, 181/255.0, 119/255.0,1));
  // light->setLinear(0.022);
  // light->setQuadratic(0.0007);
  //  lights.push_back(light);
//  seed = std::chrono::system_clock::now().time_since_epoch().count();
  seed = 38383;
  chunk_size = 64;
  Sun = new Light(DIRECTIONAL);
  lights.push_back(Sun);
}

TGenScene::~TGenScene(){
  clearCameras();
  // for(unsigned int i=0; i<lights.size(); i++){
  //   if(lights[i]!=nullptr){
  //     delete lights[i];
  //     lights[i]=nullptr;
  //   }
  delete Sun;
  // }
  if(skybox!=nullptr)
    delete skybox;

}

void TGenScene::draw(){
  if(draw_skybox){
    if(skybox!=nullptr)
      skybox->draw();
    else{
      skybox = new Cube(yuki->am);
      //std::vector<Texture*> st;
      //st.push_back(yuki->am->getTexture("totality"));
      skybox->setTexture(yuki->am->getTexture("totality"));
      skybox->setLightingOn(true);
      skybox->setMaterial(Materials::Default);
      skybox->scale(glm::vec3(100));
      skybox->setSkybox(true);

    }
  }
  if(draw_mesh){
    for(auto const& [key, val] : chunks) {
      val->draw();
    }
  }
}


void TGenScene::update(float delta){
  int viewDis = 2;
  //Camera position
  glm::vec3 cpos = getCamera()->getPosition();
  //Converted to chunk coordinates.
  int x = cpos.x/(chunk_size-2);
  int z = cpos.z/(chunk_size-2);
  //Generate range to check
  int lower_x = x-viewDis;
  int lower_z = z-viewDis;
  int upper_x = x+viewDis;
  int upper_z = z+viewDis;

  //Check all chunks that should be within our view.
  if(draw_mesh){
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
  if(event.code==sf::Keyboard::T){
    if(draw_mesh)
      draw_mesh = false;
    else
      draw_mesh = true;
  }
  if(event.code==sf::Keyboard::Y){
    if(draw_skybox)
      draw_skybox = false;
    else
      draw_skybox = true;
  }
  if(event.code==sf::Keyboard::R){
    delete skybox;
    skybox=nullptr;
  }
}

void TGenScene::keyStateEventHandler(){

}

void TGenScene::mouseButtonEventHandler(sf::Event::MouseButtonEvent event){

}

void TGenScene::mouseMoveEventHandler(sf::Event::MouseMoveEvent event){

}
