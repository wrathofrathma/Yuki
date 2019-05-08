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
  private:
    Yuki* yuki; ///< Our link back up to the rest of our resources.
    //Camera stuff
    std::map<std::string, Camera*> cameras;
    std::string active_camera;
    //Update stuff
    sf::Clock clock;
    sf::Time last_time; ///< Time variable containing our last measured time for delta calculations.
    std::vector<void (*)(Yuki*,Scene*,float)> update_events; ///< Vector containing registered events that need to update each cycle for this scene. Such as model animation.

    std::vector<Drawable*> drawables; ///< Vector containing all of the drawable objects in our scene.
    std::vector<Light*> lights; ///< Vector containing all of the light objects in our scene.

    float global_ambient; ///< A float containing our global ambient for the scene. It'll be used in our lighting updates later.

    std::vector<void (*)(sf::Event::KeyEvent event, Yuki *yu)> keyPressedEvents;
		std::vector<void (*)(Yuki *yu)> keyStateEvents;
		std::vector<void (*)(sf::Event::MouseButtonEvent event, Yuki *yu)> mouseButtonEvents;
		std::vector<void (*)(sf::Event::MouseMoveEvent event, Yuki *yu)> mouseMovedEvents;


  public:
    Scene(Yuki* yuki);
    ~Scene();

    //Runs any registered functions that need to update with the delta between updates.
    void update();
    void addUpdateFunction(void (*callback)(Yuki *yu, Scene* scene, float delta));

    void draw();

    void setGlobalAmbient(float a);
    float getGlobalAmbient();

    //Actual stuff we draw to our scene.
    void addLight(Light* l);
    void addDrawables(Drawable* d);
    std::vector<Light*> getLights();
    std::vector<Drawable*> getDrawables();

    //Camera management.
    void setActiveCamera(std::string s);
    void addCamera(std::string s, Camera* c);
    void removeCamera(std::string s);
		Camera* getCamera();

    //Adding things to our input-event loop check.
		void addKeyPressedEvent(void (*callback)(sf::Event::KeyEvent event, Yuki *yu));
		void addKeyStateEvent(void (*callback)(Yuki *yu));
		void addMouseButtonEvent(void (*callback)(sf::Event::MouseButtonEvent event, Yuki *yu));
		void addMouseMovedEvent(void (*callback)(sf::Event::MouseMoveEvent event, Yuki *yu));

    std::vector<void (*)(sf::Event::KeyEvent event, Yuki *yu)> getKeyPressedEvents();
    std::vector<void (*)(Yuki *yu)> getKeyStateEvents();
    std::vector<void (*)(sf::Event::MouseMoveEvent event, Yuki *yu)> getMouseMovedEvents();
    std::vector<void (*)(sf::Event::MouseButtonEvent event, Yuki *yu)> getMouseButtonEvents();
};

#endif
