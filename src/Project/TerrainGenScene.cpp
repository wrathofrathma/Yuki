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
#include <cmath>
#include <sstream>
#include <string>
#include "../input/UserInput.hpp"
using namespace std;

/**
\file TerrainGenScene.cpp
\brief Implementation file of TGenScene class.

\author Christopher Arausa
\date 05/14/2019
\version Final

*/

/**
\brief Constructor

This constructor sets up our scene's cameras and initializes our lighting.
\param yuki --- Yuki game engine class pointer.
*/
TGenScene::TGenScene(Yuki *yuki) : Scene(yuki){
  setGlobalAmbient(glm::vec4(0.1));
  draw_mesh = true;
  framerate = true;
  draw_skybox = true;
  addCamera("Free", new FreeCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
  addCamera("Sphere", new SphericalCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
  setActiveCamera("Free");
  skybox = nullptr;
  getCamera()->setPosition(glm::vec3(4000,30,4000));
  draw_grass = false;
  chunk_view_distance = 3;
  apply_distortion = true;
  seed = 38383;
  chunk_size = 64;
  Sun = new Light(DIRECTIONAL);
  lights.push_back(Sun);
  glLineWidth(2);
  lower_plane = glm::vec4(0,-1,0, -6);
  upper_plane = glm::vec4(0,1,0,6); //This one will create a clipping plane only rendering above a y of -6, which is our water height.
}
/**
\brief Destructor

Releases our camera memory and skybox.
*/
TGenScene::~TGenScene(){
  clearCameras();
  for(Light* l : lights){
    delete l;
  }
  if(skybox!=nullptr)
    delete skybox;
}


/**
\brief Draws our scene.
*/
void TGenScene::draw(){
  //Camera position
  glm::vec3 cpos = getCamera()->getPosition();
  //Converted to chunk coordinates.
  int x = cpos.x/(chunk_size-2);
  int z = cpos.z/(chunk_size-2);
  //Generate range to check
  int lower_x = x-chunk_view_distance;
  int lower_z = z-chunk_view_distance;
  int upper_x = x+chunk_view_distance;
  int upper_z = z+chunk_view_distance;

  glEnable(GL_CLIP_DISTANCE0);


  //Reflection framebuffer drawing.
  yuki->am->bindReflectionFB();
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(skybox!=nullptr){
    skybox->rotate(glm::vec3(0.00005,0.0,0));
    skybox->draw();
  }
  //Camera needs to change orientation and position for the reflection to render properly.
  float old_camera_height = cpos.y;
  float height_offset = 2*(old_camera_height + 6);
  cpos.y -= height_offset;

  glm::vec3 camera_orientation = getCamera()->getOrientation();
  float camera_pitch = camera_orientation.y;
  camera_orientation.y = -camera_pitch;
  getCamera()->setPosition(cpos);
  getCamera()->setOrientation(camera_orientation);

  //Update our shaders with the position and orientation for the reflection
  for(auto const& [key, val] : yuki->am->getShaders()) {
    val->bind();
    val->setVec4("plane", upper_plane);
    getCamera()->update();
    getCamera()->applyUpdate(val);
  }

  if(draw_mesh){
    for(auto const& [key, val] : chunks) {
      glm::vec2 cp = val->getPosition();
        val->draw(current_delta, false,draw_grass, apply_distortion);
    }
  }
  for(LightCube* lc : cubes){
    lc->draw();
  }

  yuki->am->unbindFB();

  //Set our camera back to its original position/orientation
  camera_orientation.y = camera_pitch;
  cpos.y += height_offset;
  getCamera()->setPosition(cpos);
  getCamera()->setOrientation(camera_orientation);
  // Refraction framebuffer drawing.
  for(auto const& [key, val] : yuki->am->getShaders()) {
    val->bind();
    val->setVec4("plane", lower_plane);
    getCamera()->update();
    getCamera()->applyUpdate(val);
  }
  yuki->am->bindRefractionFB();
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(draw_mesh){
    for(auto const& [key, val] : chunks) {
      glm::vec2 cp = val->getPosition();
      // if(abs(cp.x - x)<=chunk_view_distance && abs(cp.y - z)<=chunk_view_distance)
        val->draw(current_delta, false,draw_grass, apply_distortion);
    }
  }
  for(LightCube* lc : cubes){
    lc->draw();
  }

  yuki->am->unbindFB();

  //Real draw time.
  glDisable(GL_CLIP_DISTANCE0);
  if(draw_skybox){
    if(skybox!=nullptr)
      skybox->draw();
    else{
      skybox = new Cube(yuki->am);
      skybox->setTexture(yuki->am->getTexture("mira"));
      skybox->setLightingOn(true);
      skybox->setMaterial(Materials::Default);
      skybox->scale(glm::vec3(100));
      skybox->setSkybox(true);
    }
  }

  //Let's only draw shit near our draw distance.
  if(draw_mesh){
    for(auto const& [key, val] : chunks) {
      glm::vec2 cp = val->getPosition();
      // if(abs(cp.x - x)<=chunk_view_distance && abs(cp.y - z)<=chunk_view_distance)
        val->draw(current_delta, true,draw_grass, apply_distortion);
    }
  }
  for(LightCube* lc : cubes){
    ((Cube*)lc)->draw();
  }

}

/**
\brief Update logic called every tick.

\param delta -- float delta time since last update.
*/
void TGenScene::update(float delta){
  //Updates our mouse ray position.
  Camera* cam = getCamera();
  glm::vec2 mouse_ndc = yuki->ui->getMouseNDC();
  if(cam!=nullptr){
    mouse_caster.update(mouse_ndc,cam);
  }
  //Camera position
  glm::vec3 cpos = getCamera()->getPosition();
  //Converted to chunk coordinates.
  int x = cpos.x/(chunk_size-2);
  int z = cpos.z/(chunk_size-2);
  //Generate range to check
  int lower_x = x-chunk_view_distance;
  int lower_z = z-chunk_view_distance;
  int upper_x = x+chunk_view_distance;
  int upper_z = z+chunk_view_distance;

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
        else{

        }
      }
    }
  }
  if(framerate){
    yuki->ge->setTitle(yuki->program_title + " " +  to_string(1.0f/delta));
  }

}


/**
\brief Updates our shaders with our current lighting situation and camera matrices.
*/
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

/**
\brief Handles our key pressed toggled events

\param event --- sf::Event::KeyEvent event data
*/
void TGenScene::keyPressedEventHandler(sf::Event::KeyEvent event){
  if(event.code==sf::Keyboard::T){
    if(draw_mesh){
      cout << "Terrain off." << endl;
      draw_mesh = false;
    }
    else{
      cout << "Terrain on." << endl;
      draw_mesh = true;
    }
  }
  if(event.code==sf::Keyboard::Y){
    if(draw_skybox)
      draw_skybox = false;
    else
      draw_skybox = true;
  }
  if(event.code==sf::Keyboard::G){
    draw_grass = !draw_grass;
  }
  if(event.code==sf::Keyboard::R){
    delete skybox;
    skybox=nullptr;
  }
  if(event.code==sf::Keyboard::U){
    if(Sun->getOn())
      Sun->setOn(false);
    else
      Sun->setOn(true);
  }
  if(event.code==sf::Keyboard::F){
    if(framerate)
      framerate = false;
    else
      framerate = true;
  }
  if(event.code == sf::Keyboard::Q){
    apply_distortion = !apply_distortion;
  }
}


/**
\brief Empty key state logic handler.
*/
void TGenScene::keyStateEventHandler(){

}
/**
\brief Empty mouse button logic handler.
*/
void TGenScene::mouseButtonEventHandler(sf::Event::MouseButtonEvent event){
  if(event.button == sf::Mouse::Right){
    if(lights.size()==10){
      delete lights[0];
      lights.pop_front();
      cubes.pop_front();
    }
    LightCube *lc = new LightCube(asset_manager);
    glm::vec3 ray_dir = mouse_caster.getRay();
    glm::vec3 cpos = getCamera()->getPosition();
    ray_dir *= 30;
    lc->setAmbient(glm::vec4(0.8,0,0,0));
    glm::vec3 lpos = cpos + ray_dir;
    lc->setMaterial(Materials::Default);
    lc->setPosition(glm::vec3(lpos));
    cubes.push_back(lc);
    lights.push_back(lc);
  }
}
/**
\brief Empty mouse move logic handler.
*/
void TGenScene::mouseMoveEventHandler(sf::Event::MouseMoveEvent event){

}
