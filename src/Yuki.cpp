#include "Yuki.hpp"
#include "UserInput.hpp"
#include "graphics/GraphicsEngine.hpp"
#include "graphics/Scene.hpp"
#include "AssetManager.hpp"

Yuki::Yuki(bool debug){
	DEBUG = debug;
	program_title = "Yuki ";
	program_title+=VERSION;
	std::cout << "Version: " << program_title << std::endl;
	ge = nullptr;
	am = nullptr;
	ui = nullptr;
	init();
}

Yuki::~Yuki(){
	//Cleanup our scenes.
	while(scenes.size()>0){
		std::map<std::string, Scene*>::iterator it = scenes.begin();
		if(it->second!=nullptr){
			delete it->second;
			it->second = nullptr;
		}
		scenes.erase(it);
	}

	if(ui!=nullptr)
		delete ui;
	if(ge!=nullptr)
		delete ge;
	if(am!=nullptr)
		delete am;
}

void Yuki::close(){
	ge->close();
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
	am = new AssetManager();
	//If things load decently, we can then create our window
	ge = new GraphicsEngine(this, program_title, opengl_major, opengl_minor);

	//Once that's all nice and finished, let's start our primary event loop.
	ui = new UI(this);

}

void Yuki::run(){
	while(ge->isOpen()){
		if(ui!=nullptr)
			ui->processInput();
		Scene *s = getActiveScene();
		if(s!=nullptr)
			s->processInput();
		ge->display(s);
	}
}

void Yuki::addScene(std::string id, Scene* scene){
	if(scenes.count(id)>0){
		std::cerr << "Scene by this ID already exists. Overwriting old scene." << std::endl;
		removeScene(id);
	}
	scenes.insert(std::pair<std::string, Scene*>(id,scene));
}

void Yuki::setActiveScene(std::string s){
	if(scenes.size()==0){
		std::cerr << "Can't set active scene, no registered scenes." << std::endl;
		return;
	}
	if(scenes.count(s)==0){
		std::cerr << "Can't set active scene. Scene ID not found." << std::endl;
		return;
	}
	active_scene = s;
}

void Yuki::removeScene(std::string s){
	if(scenes.size()==0)
		return;
	if(scenes.count(s)==0)
		return;
	//The actual deletion
	if(scenes[s]!=nullptr){
		delete scenes[s];
		scenes[s] = nullptr;
	}
	scenes.erase(s);
	//If our deleted scene was our primary scene, then we should pick the scene at the bottom of the map. If one doesn't exist then we just set to "".
	if(active_scene.compare(s)==0){
		if(scenes.size()>0)
			active_scene = scenes.begin()->first;
		else
			active_scene.clear();
	}
}

Scene* Yuki::getActiveScene(){
	if(scenes.size()==0){
		std::cerr << "Can't retrieve active scene, no registered scenes." << std::endl;
		return nullptr;
	}
	if(active_scene.size()==0){
		std::cerr << "Can't retrieve active scene. Active scene ID not set." << std::endl;
		return nullptr;
	}
	if(scenes.count(active_scene)==0){
		std::cerr << "Can't retrieve active scene. Scene ID not found." << std::endl;
		return nullptr;
	}
	return scenes[active_scene];
}
