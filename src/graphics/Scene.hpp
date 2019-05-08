#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

#include <SFML/System.hpp>
class Yuki;
class Camera;
class Light;
class Drawable;
class AssetManager;

/**
\file Scene.hpp
\brief header file for Scene.cpp

\author Christopher Arausa
\version 0.1
\date 5/7/2019

*/

/**
\class AssetManager

\brief The scene class is a top level container to hold all relevant objects and functions relative to a scene or area.
Things such as UI input handling methods, drawable objects, lighting objects, update logic threads. Etc.
For now these are opaque to make things simple.
*/

class Scene {
  protected:
    Yuki* yuki; ///< Our link back up to the rest of our resources.
    AssetManager* asset_manager; ///< Having a direct link to our asset manager is handy.
    //Camera stuff
    std::map<std::string, Camera*> cameras;
    std::string active_camera;

    //Update stuff
    sf::Time last_time; ///< Time variable containing our last measured time for delta calculations.
    sf::Clock clock;

    std::vector<Drawable*> drawables; ///< Vector containing all of the drawable objects in our scene.
    std::vector<Light*> lights; ///< Vector containing all of the light objects in our scene.

    float global_ambient; ///< A float containing our global ambient for the scene. It'll be used in our lighting updates later.

  public:
    Scene(Yuki* yuki);
    virtual ~Scene();
    void tick(); //Handles pre-update events such as calcing delta time and updating camera matrices.
    //Scene logic function.
    virtual void update();
    //Scene draw function.
    virtual void draw();
    //Functions that will determine how our scene handles input.
    virtual void keyPressedEventHandler(sf::Event::KeyEvent event);
    virtual void keyStateEventHandler();
    virtual void mouseButtonEventHandler(sf::Event::MouseButtonEvent event);
    virtual void mouseMoveEventHandler(sf::Event::MouseMoveEvent event);

    void setGlobalAmbient(float a);
    float getGlobalAmbient();

    //Actual stuff we draw to our scene. This is subject to change later.
    void addLight(Light* l);
    void addDrawables(Drawable* d);
    std::vector<Light*> getLights();
    std::vector<Drawable*> getDrawables();

    //Camera management.
    void setActiveCamera(std::string s);
    void addCamera(std::string s, Camera* c);
    void removeCamera(std::string s);
		Camera* getCamera();

};

#endif
