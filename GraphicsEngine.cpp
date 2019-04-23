#include "GraphicsEngine.hpp"
GraphicsEngine::GraphicsEngine(std::string title, GLint MajorVersion, GLint MinorVersion, int width, int height) :
	sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24,8,4,MajorVersion, MinorVersion, sf::ContextSettings::Core)) {
	setActive();
	glClearColor(0, 0, 0, 1);
	resize();
	setVisible(true);

}

GraphicsEngine::~GraphicsEngine(){

}

void GraphicsEngine::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sf::RenderWindow::display();
}
void GraphicsEngine::screenshot(){

}
void GraphicsEngine::resize(){

}
void GraphicsEngine::setSize(unsigned int w, unsigned int h){

}
