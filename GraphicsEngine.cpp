#include "GraphicsEngine.hpp"
#include "Yuki.hpp"

GraphicsEngine::GraphicsEngine(Yuki* yu, std::string title, GLint MajorVersion, GLint MinorVersion, int width, int height) :
	sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24,8,4,MajorVersion, MinorVersion, sf::ContextSettings::Core)) {

	yuki = yu;
	setActive();
	glClearColor(0, 0, 0, 1);
	sscount = 0;
	poly = new Polygon(yuki->am);
	//poly2 = new Polygon(yuki->am);
	//Testing Camera stuff
	Shader shader("shaders/2DBasic");
	cameras.insert(std::pair<std::string, Camera*>("default", new Camera(shader.getUniformLocation("proj"), shader.getUniformLocation("view"), getSize().x, getSize().y, 50.0f)));
	setActiveCamera("default");

	// Testing polygon stuff
	// float vv[] = {
	//      0.5f,  0.5f, 0.0f, 1.0f, // top right
	//      0.5f, -0.5f, 0.0f, 1.0f, // bottom right
	//     -0.5f, -0.5f, 0.0f, 1.0f, // bottom left
	//     -0.5f,  0.5f, 0.0f,  1.0f  // top left
	// };
	unsigned int vi[] = {0, 1, 2,
		2, 3, 0,
		6, 5, 4,
		4, 7, 6,
		10, 9, 8,
		8, 11, 10,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		22, 21, 20,
		20, 23, 22
		};
	GLfloat vv[] = {-0.5, 0.5, 0.5, 1,
	  -0.5, -0.5, 0.5, 1,
	  0.5, -0.5, 0.5, 1,
	  0.5, 0.5, 0.5, 1,

	  -0.5, 0.5, -0.5, 1,
	  -0.5, -0.5, -0.5, 1,
	  0.5, -0.5, -0.5, 1,
	  0.5, 0.5, -0.5, 1,

	  -0.5, 0.5, 0.5, 1,
	  -0.5, 0.5, -0.5, 1,
	  0.5, 0.5, -0.5, 1,
	  0.5, 0.5, 0.5, 1,

	  -0.5, -0.5, 0.5, 1,
	  -0.5, -0.5, -0.5, 1,
	  0.5, -0.5, -0.5, 1,
	  0.5, -0.5, 0.5, 1,

	  0.5, -0.5, 0.5, 1,
	  0.5, -0.5, -0.5, 1,
	  0.5, 0.5, -0.5, 1,
	  0.5, 0.5, 0.5, 1,

	  -0.5, -0.5, 0.5, 1,
	  -0.5, -0.5, -0.5, 1,
	  -0.5, 0.5, -0.5, 1,
	  -0.5, 0.5, 0.5, 1,
	 };
	std::vector<float> vertices (vv, vv+96);
	std::vector<unsigned int> indices(vi, vi+36);
	// indices.push_back(0);
	// indices.push_back(1);
	// indices.push_back(3);
	// indices.push_back(1);
	// indices.push_back(2);
	// indices.push_back(3);
	// poly2->loadVertices(vertices, indices);
	 poly->loadVertices(vertices, indices);
	float colors[] = {
		1, 1, 1,
		0.5, 1, 1,
		1, 0.5, 1,
		1, 1, 0.5
	};
	std::vector<float> cs (colors, colors+12);
	yuki->am->loadTexture("textures/test.jpg", "doge");
	//poly->setColor(cs);
	poly->setTexture(yuki->am->getTexture("doge"));
	//poly2->setTexture(yuki->am->getTexture("doge"));

	//End of polygon tests

	wireframe = false;
	setVerticalSyncEnabled(true);
}

GraphicsEngine::~GraphicsEngine(){
	std::map<std::string, Camera*>::iterator it = cameras.begin();
	for( ; it!=cameras.end(); it++){
		delete it->second;
	}
	cameras.clear();
	delete poly;
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
	poly->rotate(glm::vec3(0.01, -0.01, 0));
	//poly->scale(glm::vec3(0.005, 0.005, 0.005));
	//poly->translate(glm::vec3(0.0, 0.1, 0.0));
	poly->draw();
	//poly2->draw();


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
