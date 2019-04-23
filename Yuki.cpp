#include "Yuki.hpp"
#include "UserInput.hpp"

Yuki::Yuki(bool debug){
	DEBUG = debug;
	program_title = "Yuki ";
	program_title+=VERSION;
	std::cout << "Version: " << program_title << std::endl;
	ge = nullptr;
	am = nullptr;
	ui = nullptr;
	running = true;
	init();
}

Yuki::~Yuki(){
	if(ui!=nullptr)
		delete ui;
	if(ge!=nullptr)
		delete ge;
	if(am!=nullptr)
		delete am;
}

void Yuki::close(){
	running = false;

}

bool Yuki::isRunning(){
	return running;
}
void Yuki::checkOpenGL(){
	//Straight up yoinked most of this from my graphics professor's code. It seems useful.
	GLint MinMajor = 3;
	GLint MinMinor = 3;
	GLint WindowWidth = 800;
	GLint WindowHeight = 600;

	//Make a test window requesting OpenGL version 10.10 and seeing what it falls back to.
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "OpenGL Setup", sf::Style::Default, sf::ContextSettings(24, 8, 4, 10, 10, sf::ContextSettings::Core));
	window.setVisible(false);

	if(glewInit()){
		std::cerr << "Unable to initialize GLEW ... exiting." << std::endl;
		exit(-1);
	}

	glGetIntegerv(GL_MAJOR_VERSION, &opengl_major);
	glGetIntegerv(GL_MINOR_VERSION, &opengl_minor);

	bool versionOkay = true;
	if(opengl_major < MinMajor)
		versionOkay = false;
	else if (opengl_minor < MinMinor)
		versionOkay = false;

	if(!versionOkay){
        std::cerr << "Graphics card OpenGL version is " << opengl_major << "." << opengl_minor << std::endl;
        std::cerr << "Program required OpenGL version is " << MinMajor << "." << MinMinor << std::endl;
        std::cerr << "Exiting" << std::endl;;
        exit(-1);
    }

    if (DEBUG){
        std::cout << std::endl;
        std::cout << "Version  = " << glGetString(GL_VERSION) << std::endl;
        std::cout << "Major    = " << opengl_major << std::endl;
        std::cout << "Minor    = " << opengl_minor << std::endl;
        std::cout << "Vendor   = " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "Renderer = " << glGetString(GL_RENDERER) << std::endl;
        std::cout << std::endl;
    }

    window.close();
}
void Yuki::init(){
	//First check to see if our computer supports our OpenGL version
	checkOpenGL();
	//If everything didn't explode by now, we can load our assets

	//If things load decently, we can then create our window
	ge = new GraphicsEngine(program_title, opengl_major, opengl_minor);

	//Once that's all nice and finished, let's start our primary event loop.
	ui = new UI(this);

	//Start our input thread.
	ui->start();
}
