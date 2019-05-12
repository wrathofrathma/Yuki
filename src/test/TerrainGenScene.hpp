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
class Light;
class Yuki;
class Mesh;
class Quad;
class TerrainChunk;
class Light;
class TGenScene : public Scene {
  private:
    Cube* skybox;
    std::map<std::pair<int,int>, TerrainChunk*> chunks;
    std::vector<Light*> lights;
    bool draw_mesh;
    bool draw_skybox;
    Light *Sun;
    std::vector<Quad> grass;
    int chunk_view_distance;
    bool framerate;
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
