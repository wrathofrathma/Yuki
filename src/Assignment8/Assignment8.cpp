#include "Assignment8.hpp"
/**
\file Assignment8.cpp
\brief Implementation of the SchoolScene class.

\author Christopher Arausa
\version Final
\date 05/09/2019

*/


/**
\brief Constructor

This constructor fully sets up the scene. Generating all textures, cubes, coordinates, cameras, etc.
\param yuki --- Yuki game engine class pointer.
*/
SchoolScene::SchoolScene(Yuki *yuki) : Scene(yuki) {
  //Well first off we have two cameras.
  setGlobalAmbient(0.8);
  addCamera("Free", new FreeCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
  addCamera("Sphere", new SphericalCamera(yuki->ge->getSize().x, yuki->ge->getSize().y, 50.0f));
  setActiveCamera("Free");
  getCamera()->setPosition(glm::vec3(0,10,-10));
  ((FreeCamera *)getCamera())->rotate(glm::vec3(2.7,0,0));

  //Let's generate our skybox.
  skybox = new Cube(yuki->am);
  skybox->setTexture(yuki->am->getTexture("totality"));
  skybox->setLightingOn(false);
  skybox->setMaterial(Materials::bluePlastic);
  skybox->scale(glm::vec3(200));
  skybox->setSkybox(true);

  //Let's grab the cube textures.
  std::vector<Texture*> texts;
  texts.push_back(asset_manager->getTexture("cat1"));
  texts.push_back(asset_manager->getTexture("cat2"));
  texts.push_back(asset_manager->getTexture("cat3"));
  texts.push_back(asset_manager->getTexture("doge"));
  texts.push_back(asset_manager->getTexture("doge"));
  texts.push_back(asset_manager->getTexture("doge"));
  int x = 0;
  int y = 0;
  int z = 0;
  //Create random number generator.
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,16);

  for(int i=0; i<50; i++){
    TestCube *t = new TestCube(asset_manager);
    t->setTexture(texts);
    t->setMaterial(Materials::Default);

    x = dis(gen) - 7;
    y = dis(gen) + 2;
    z = dis(gen) - 7;
    t->translate(glm::vec3(x,y,z));
    cubes.push_back(t);
  }
  //We also have a flat ground plane.
  Quad *plane = new Quad(asset_manager);
  plane->setTexture("stone");
  plane->scale(glm::vec3(200.0f));
  plane->rotate(glm::vec3(0,1.57,0));
  plane->setMaterial(Materials::greenTint);
  addDrawables(plane);

  //I like having a wall of rotating cats.
  Quad* wall1 = new Quad(asset_manager);
  wall1->setShader("Rotate");
  wall1->setTexture("cat1");
  wall1->scale(glm::vec3(20.f));
  wall1->setPosition(glm::vec3(0,10,-50));
  wall1->setMaterial(Materials::Default);
  addDrawables(wall1);

  //Lighting replicating similar variables to what was provided.
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

  addLight(ol);
  addLight(ol1);
  addLight(ol2);

  cube_rotate = false;
  text_rotate = false;
}

/**
\brief Destructor

Releases all memory used by this scene for cameras, cubes, lights, the plane, the wall.
*/
SchoolScene::~SchoolScene(){
  while(cameras.size()>0){
    std::map<std::string, Camera*>::iterator it = cameras.begin();
    if(it->second!=nullptr){
      delete it->second;
      it->second = nullptr;
    }
    cameras.erase(it);
  }
  for(unsigned int i=0; i<lights.size(); i++){
    if(lights[i]!=nullptr){
      delete lights[i];
      lights[i]=nullptr;
    }
  }
  for(unsigned int i=0; i<drawables.size(); i++){
    if(drawables[i]!=nullptr){
      delete drawables[i];
      drawables[i]=nullptr;
    }
  }
  for(unsigned int i=0; i<cubes.size(); i++){
    if(cubes[i]!=nullptr){
      delete cubes[i];
      cubes[i]=nullptr;
    }
  }
  delete skybox;
}


/**
\brief Our update loop function.

It updates the shader's texture translation and rotates the cubes both according to whether the boolean values for text_rotate and cube_rotate are on.
\param delta --- Delta time between calls.
*/
void SchoolScene::update(float delta){
   if(text_rotate){
    //asset_manager->getShader("Rotate")->bind();
    asset_manager->getShader("Rotate")->setFloat("time",clock.getElapsedTime().asSeconds()/2.0);
  }
  if(cube_rotate){
    for(TestCube* c : cubes){
      c->rotate();
    }
  }
}

/**
\brief This draws our scene. Nothing fancy, just drawing our cubes & drawables.
*/
void SchoolScene::draw(){
  skybox->draw();

  for(Drawable* d : drawables)
    d->draw();

  for(TestCube* c : cubes){
    c->draw();
  }

  // skybox->draw();

  // glDepthMask(GL_FALSE);
  // glDepthFunc(GL_LEQUAL);
  // glDisable(GL_DEPTH_TEST);
 // skybox->draw();
  // glEnable(GL_DEPTH_TEST);
  // glDepthMask(GL_TRUE);
  // glDepthFunc(GL_LESS);
}

/**
\brief This function handles the scene specific key pressed events.

Global key pressed events(such as camera selection and screnshots) can be found in the main.cpp file.
\param event --- The specific sf::Event::KeyEvent that triggered.
*/
void SchoolScene::keyPressedEventHandler(sf::Event::KeyEvent event){
  switch(event.code){
    case sf::Keyboard::T:
      if(text_rotate==false)
        text_rotate = true;
      else
        text_rotate = false;
      break;
    case sf::Keyboard::R: {
      if(cube_rotate==true){
        for(TestCube *c : cubes)
          c->setRotateVector(glm::vec3(0));
          cube_rotate=false;
        }
      else {
        cube_rotate = true;
        srand(time(nullptr));
        glm::vec3 rot_vector;
        for(TestCube *c : cubes){
          rot_vector.x = (rand()% 100)/1000.0;
          rot_vector.y = (rand()% 100)/1000.0;
          rot_vector.z = (rand()% 100)/1000.0;
          c->setRotateVector(rot_vector);
        }
      }
      }
      break;
    case sf::Keyboard::F1:
      //Toggle ground lights on
      drawables[0]->setLightingOn(true);
      break;
    case sf::Keyboard::F2:
      //Toggle ground lights off
      drawables[0]->setLightingOn(false);
      break;
    case sf::Keyboard::F3:
      //Toggle ground texture on
      drawables[0]->setUseTexture(true);
      break;
    case sf::Keyboard::F4:
      //toggle ground texture off.
      drawables[0]->setUseTexture(false);
      break;
    case sf::Keyboard::F5:
      //Turn on cube lights
      for(TestCube *c : cubes){
        c->setLightingOn(true);
      }
      break;
    case sf::Keyboard::F6:
      //turn off cube lights
      for(TestCube *c : cubes){
        c->setLightingOn(false);
      }
      break;
    case sf::Keyboard::F7:
      //Turn on cube texture.
      for(TestCube* c : cubes){
        c->setUseTexture(true);
      }
      break;
    case sf::Keyboard::F8:
      //Turn off cube textures.
      for(TestCube* c : cubes){
        c->setUseTexture(false);
      }
      break;
    default:
      break;
  };
}
/**
\brief This function handles the scene specific key state events.

Global key state events(such as camera movement) can be found in the main.cpp file.
*/
void SchoolScene::keyStateEventHandler(){}
/**
\brief This function handles the scene specific mouse button pressed events.
\param event --- The specific sf::Event::MouseButtonEvent that triggered.
*/
void SchoolScene::mouseButtonEventHandler(sf::Event::MouseButtonEvent event){}
/**
\brief This function handles the scene specific move move events.

Global key pressed events(such as camera movement) can be found in the main.cpp file.
\param event --- The specific sf::Event::MouseMoveEvent that triggered.
*/
void SchoolScene::mouseMoveEventHandler(sf::Event::MouseMoveEvent event){}
