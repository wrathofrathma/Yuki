#ifndef TGEN_SCENE
#define TGEN_SCENE
#include <iostream>
#include <vector>
#include <thread>
#include <map>
#include <chrono>
#include "../graphics/Scene.hpp"
#include "../graphics/drawables/Mesh.hpp"
using namespace std;

class Yuki;
class Cube;
class TerrainChunk;
class Light;
class TGenScene : public Scene {
  private:
    Cube* skybox;
    std::map<std::pair<int,int>, TerrainChunk*> chunks;
    std::vector<Light*> lights;

  public:
    TGenScene(Yuki *yuki);
    ~TGenScene();
    unsigned int seed;
    unsigned int chunk_size;
    void draw();
    void update(float delta);
    void updateShaders();
    void keyPressedEventHandler(sf::Event::KeyEvent event);
    void keyStateEventHandler();
    void mouseButtonEventHandler(sf::Event::MouseButtonEvent event);
    void mouseMoveEventHandler(sf::Event::MouseMoveEvent event);

    static void tChunkGen(TGenScene* tgs, int x, int z, int seed);
};

#endif
