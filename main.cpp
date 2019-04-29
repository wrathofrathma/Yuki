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
