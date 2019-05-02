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
			cout << "W" << endl;
			break;
		case sf::Keyboard::A:
			cout << "A" << endl;
			break;
		case sf::Keyboard::S:
			cout << "S" << endl;
			break;
		case sf::Keyboard::D:
			cout << "D" << endl;
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
