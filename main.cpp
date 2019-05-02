#include <iostream>
#include "Yuki.hpp"
#include <thread>

using namespace std;

#include "Shader.hpp"

void moveEvent(sf::Event::MouseMoveEvent event, Yuki *yu){
	//cout << "Mouse moved!" << endl;
}
void keyPressedEvent(sf::Event::KeyEvent event, Yuki *yu){
//	cout << "Key pressed!" << endl;
	switch(event.code){
		case sf::Keyboard::W:
			yu->ge->getCamera()->move(glm::vec3(0,0,-0.1));
			break;
		case sf::Keyboard::A:
			yu->ge->getCamera()->move(glm::vec3(-0.1,0,0));
			break;
		case sf::Keyboard::S:
			yu->ge->getCamera()->move(glm::vec3(0,0,0.1));
			break;
		case sf::Keyboard::D:
			yu->ge->getCamera()->move(glm::vec3(0.1,0,0));
			break;
		case sf::Keyboard::Up:
			yu->ge->getCamera()->rotate(glm::vec3(0,0.1,0));
			break;
		case sf::Keyboard::Down:
			yu->ge->getCamera()->rotate(glm::vec3(0,-0.1,0));
			break;
		case sf::Keyboard::Left:
			yu->ge->getCamera()->rotate(glm::vec3(-0.1,0,0));
			break;
		case sf::Keyboard::Right:
			yu->ge->getCamera()->rotate(glm::vec3(0.1,0,0));
			break;
		case sf::Keyboard::Space:
			yu->ge->getCamera()->move(glm::vec3(0,0.1,0));
			break;
		case sf::Keyboard::LShift:
			yu->ge->getCamera()->move(glm::vec3(0,-0.1,0));
			break;
		case sf::Keyboard::Escape:
			yu->close();
			break;
	  default:
			break;
	};
}
void mouseButtonEvent(sf::Event::MouseButtonEvent event, Yuki *yu){
//	cout << "Mouse button pressed!" << endl;
}
void stateProcessing(Yuki *yu){
//	cout << "Mouse moved!" << endl;
}

int main(){
	Yuki yuki;
	yuki.ui->addKeyPressedEvent(keyPressedEvent);
	yuki.ui->addMouseMovedEvent(moveEvent);
	yuki.ui->addMouseButtonEvent(mouseButtonEvent);


	yuki.run();
	return 0;
}
