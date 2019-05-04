#include "GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine(Yuki* yu, std::string title, GLint MajorVersion, GLint MinorVersion, int width, int height) :
	sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24,8,4,MajorVersion, MinorVersion, sf::ContextSettings::Core)) {

	yuki = yu;
	setActive();
	glClearColor(0, 0, 0, 1);
	sscount = 0;
	yuki->am->loadShaderIndex(); // We need to call this from here because we need an active opengl context.
	yuki->am->loadTextureIndex(); //We also need an active context for this too.
	//Need to grab a shader so we can get the uniform locations we need for our camera.
	Shader *shader = yuki->am->getShader("2DBasic");
	shader->bind(); //Need to bind our shader before doing anything else since we are about to mess with uniforms.
	//Generate an active camera labeled "default"
	cameras.insert(std::pair<std::string, Camera*>("default", new Camera(shader->getUniformLocation("proj"), shader->getUniformLocation("view"), getSize().x, getSize().y, 50.0f)));
	setActiveCamera("default");


	quad = new Quad(yuki->am);
	quad->setTexture(yuki->am->getTexture("doge"));
	cube = new Cube(yuki->am);
	//poly->setTexture(yuki->am->getTexture("doge"));

	//End of polygon tests

	wireframe = false;
	setVerticalSyncEnabled(true);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	cube->scale(glm::vec3(2.0f));
}

GraphicsEngine::~GraphicsEngine(){
	std::map<std::string, Camera*>::iterator it = cameras.begin();
	for( ; it!=cameras.end(); it++){
		delete it->second;
	}
	cameras.clear();
	delete quad;
	delete cube;
}
bool GraphicsEngine::getWireframe(){
	return wireframe;
}
void GraphicsEngine::setActiveCamera(std::string c){
	if(cameras.count(c) > 0)
		active_camera = c;
}

void GraphicsEngine::setWireframe(bool v){
	if(wireframe != v)
		toggleWireframe();
	wireframe = v;
}
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
void GraphicsEngine::display(){
	glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cameras[active_camera]->update();
	quad->draw();

	cube->draw();

	sf::RenderWindow::display();
	printOpenGLErrors();
}

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

Camera* GraphicsEngine::getCamera(){
	return cameras[active_camera];
}
