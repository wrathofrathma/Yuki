#include "GraphicsEngine.hpp"
#include "Yuki.hpp"

GraphicsEngine::GraphicsEngine(Yuki* yu, std::string title, GLint MajorVersion, GLint MinorVersion, int width, int height) :
	sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24,8,4,MajorVersion, MinorVersion, sf::ContextSettings::Core)) {

	yuki = yu;
	setActive();
	glClearColor(0, 0, 0, 1);
	sscount = 0;
	//Testing Camera stuff
	Shader shader("shaders/2DBasic");
	cameras.insert(std::pair<std::string, Camera*>("default", new Camera(shader.getUniformLocation("proj"), shader.getUniformLocation("view"), getSize().x, getSize().y, 50.0f)));
	setActiveCamera("default");

	// Testing polygon stuff
	float vv[] = {
	     0.5f,  0.5f, 0.0f, 1.0f, // top right
	     0.5f, -0.5f, 0.0f, 1.0f, // bottom right
	    -0.5f, -0.5f, 0.0f, 1.0f, // bottom left
	    -0.5f,  0.5f, 0.0f,  1.0f  // top left
	};
	std::vector<float> vertices (vv, vv+16);
	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	poly.loadVertices(vertices, indices);
	float colors[] = {
		1, 1, 1,
		0.5, 1, 1,
		1, 0.5, 1,
		1, 1, 0.5
	};
	std::vector<float> cs (colors, colors+12);
	yuki->am->loadTexture("textures/test.jpg", "doge");
	//poly.setColor(cs);
	poly.setTexture(yuki->am->getTexture("doge"));
	poly.setUseTexture(true)
	//End of polygon tests

	;
	wireframe = false;
	setVerticalSyncEnabled(true);
}

GraphicsEngine::~GraphicsEngine(){
	std::map<std::string, Camera*>::iterator it = cameras.begin();
	for( ; it!=cameras.end(); it++){
		delete it->second;
	}
	cameras.clear();
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

	poly.draw();



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
