#include "GraphicsEngine.hpp"
#include "../Yuki.hpp"
#include "Scene.hpp"
#include "cameras/Camera.hpp"
#include "../AssetManager.hpp"
#include "components/Light.hpp"
/**
\file GraphicsEngine.cpp
\brief Implementation of the GraphicsEngine class.

\author    Christopher Arausa
\version   0.1
\date      05/8/2019

*/

/**
\brief Constructor

Constructs the renderwindow using default or passed values. Also calls the asset manager to load shader and texture indexes now that we have an active OpenGL context.
\param yu --- Yuki game engine pointer.
\param title --- Window title.
\param MajorVersion --- OpenGL major version to use.
\param MinorVersion --- OpenGL minor version to use.
\param width --- Window width.
\param height --- Window height.
*/
GraphicsEngine::GraphicsEngine(Yuki* yu, std::string title, GLint MajorVersion, GLint MinorVersion, int width, int height) :
	sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24,8,4,MajorVersion, MinorVersion, sf::ContextSettings::Core)) {

	yuki = yu;
	setActive();
	glClearColor(0, 0, 0, 1);
	sscount = 0;
	yuki->am->loadShaderIndex(); // We need to call this from here because we need an active opengl context.
	yuki->am->loadTextureIndex(); //We also need an active context for this too.

	wireframe = false;
	setVerticalSyncEnabled(true);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
/**
\brief Destructor

Default empty destructor.
*/
GraphicsEngine::~GraphicsEngine(){

}
/**
\brief Returns whether we're drawing only the wireframe or the filled objects.
*/
bool GraphicsEngine::getWireframe(){
	return wireframe;
}

/**
\brief Sets whether to draw the wireframe or filled objects.
\param v --- Boolean value to set it to.
*/
void GraphicsEngine::setWireframe(bool v){
	if(wireframe != v)
		toggleWireframe();
	wireframe = v;
}
/**
\brief Toggles the wireframe on or off.
*/
void GraphicsEngine::toggleWireframe(){
	if(wireframe){
		wireframe = false;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else{
		wireframe = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}
/**
\brief Applies updates of the scene lighting to the shaders.

This is probably going to be removed eventually.
\param scene --- The scene to apply updates from.
*/
void GraphicsEngine::updateShaders(Scene *scene){
	Camera* camera = scene->getCamera();
	for(auto const& [key, val] : yuki->am->getShaders()) {
		if(camera!=nullptr){
			camera->applyUpdate(val);
		}
		val->setFloat("global_ambient", scene->getGlobalAmbient());
		unsigned int ds = 0;
	  unsigned int ss = 0;
		unsigned int ps = 0;
		std::vector<Light*> lights = scene->getLights();
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
\brief Draws the current scene and prints any OpenGL errors.
\param scene --- Scene to draw.
*/
void GraphicsEngine::display(Scene *scene){
	glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(scene!=nullptr){
		updateShaders(scene);
		scene->draw();
	}
	sf::RenderWindow::display();
	printOpenGLErrors();
}
/**
\brief Resizes the OpenGL viewport using the window size.
*/
void GraphicsEngine::resize(){
	glViewport(0,0,getSize().x,getSize().y);

}
void GraphicsEngine::setSize(unsigned int w, unsigned int h){
	sf::RenderWindow::setSize(sf::Vector2u(w,h));
	resize();
}
/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.png.

*/
void GraphicsEngine::screenshot()
{
    char ssfilename[100];
    sprintf(ssfilename, "ScreenShot%d.png", sscount);
    sf::Vector2u windowSize = getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(*this);
    sf::Image img = texture.copyToImage();
    img.saveToFile(ssfilename);
    sscount++;
}
