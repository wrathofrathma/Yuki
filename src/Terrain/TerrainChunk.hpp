#ifndef TERRAIN_CHUNK_HPP
#define TERRAIN_CHUNK_CPP
#include "../graphics/drawables/Mesh.hpp"
#include "HeightGenerator.hpp"
#include <thread>
#include <SFML/System.hpp>
#include "HeightGenerator.hpp"
class Texture;
class AssetManager;
class Mesh;
class Light;
class Quad;
#include "Water.hpp"
#include "Grass.hpp"

/**
\file TerrainChunk.hpp
\brief Header file for TerrainChunk.cpp

\author Christopher Arausa
\date 05/14/2019
\version Final
*/

/**
\class TerrainChunk
\brief The terrain chunk class will represent a 32x32 x/z area of terrain to render.

The purpose of this is primarily to allow for infinite terrain generation without loading too much at once.
We inherit the drawable class because there are too many good utility functions I dont' want to write and document again.
*/
class TerrainChunk {
  private:
    int cx; //The chunk's location in the world.
    int cz; //The chunk's location in the world.
    unsigned int chunk_size; ///< Units on each size of the chunk
    unsigned int side_vertices; ///< This will control the number of vertices on the sides. This is ratioed with chunk_size for varying levels of detail.
    unsigned int seed; ///< The seed for the chunk
    Mesh mesh; ///< The chunk's mesh data
    Mesh water_mesh; ///< (DEPRECATED) Our water mesh should be at sea level and always flat(ish)
    Quad *water_quad; ///< (DEPRECATED) old water quad
    std::thread gen_thread; ///< The thread uses during generation.
    GrassPatch grass; /// Our grass patch object.
    sf::Clock clock; ///< sfml clock to track timing.
    std::vector<Texture*> textures; ///< All textures we'd need to render our terrain.
    HeightGenerator water_rip; ///< (DEPRECATED)Water ripple heightmap generator.
    Water *waterQ; ///< Water class
  public:
    TerrainChunk(AssetManager* am, int x, int z, unsigned int seed=0,  unsigned int chunk_size = 32, unsigned int side_vertices=32);
    ~TerrainChunk();
    static void generateChunk(TerrainChunk* t);
    void draw(float delta, bool draw_w, bool draw_g, bool water_distortion);
    Mesh& getMesh();
    void setReady(bool ready){ is_ready = ready;}
    unsigned int getSeed(){ return seed; }
    AssetManager* asset_manager;
    float getHeight(int x, int z);
    float heights[128][128]; ///< Stored heights of the heightmap from generation.
    bool is_ready; ///< Is the chunk ready to be loaded?
    glm::vec2 getPosition();
    void toggleGrass();
};

#endif
