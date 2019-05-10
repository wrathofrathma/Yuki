#ifndef TERRAIN_CHUNK_HPP
#define TERRAIN_CHUNK_CPP
#include "../graphics/drawables/Mesh.hpp"
#include "HeightGenerator.hpp"
#include <thread>
class AssetManager;
class HeightGenerator;
/**
\class TerrainChunk
\brief The terrain chunk class will represent a 32x32 x/z area of terrain to render.

The purpose of this is primarily to allow for infinite terrain generation without loading too much at once.
We inherit the drawable class because there are too many good utility functions I dont' want to write and document again.
*/
class TerrainChunk {
  private:
    int cx;
    int cz;
    unsigned int seed;
    AssetManager* asset_manager;
    Mesh mesh;
    bool is_ready; ///< Is the chunk ready to be loaded?
    std::thread gen_thread;
  public:
    TerrainChunk(AssetManager* am, int x, int z, unsigned int seed=0);
    ~TerrainChunk();
    static void generateChunk(TerrainChunk* t);
    void draw();
    Mesh& getMesh();
    void setReady(bool ready){ is_ready = ready;}
    unsigned int getSeed(){ return seed; }
};

#endif
