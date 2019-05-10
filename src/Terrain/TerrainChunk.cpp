#include "HeightGenerator.hpp"
#include "../AssetManager.hpp"
#include "TerrainChunk.hpp"
#include <random>

#include <cstdlib>
#include <ctime>
TerrainChunk::TerrainChunk(AssetManager* am, int x, int z, unsigned int seed, unsigned int chunk_size, unsigned int side_vertices){
  if(seed!=0)
    this->seed = seed;
  else{
    srand(time(nullptr));
    seed = rand() % 100000 + 1;
  }
  this->asset_manager = am;
  mesh.setShader(asset_manager->getShader("Default"));

  mesh.setMaterial(Materials::Default);
  //Chunk x & z coordinates.
  cx = x;
  cz = z;

  mesh.setPosition(glm::vec3(x*chunk_size,0,z*chunk_size));
  //mesh.scale(glm::vec3(1.03,0,1.03));
  is_ready = false;
  this->side_vertices = side_vertices;
  this->chunk_size = chunk_size;
  //this->chunk_size=800;
}

TerrainChunk::~TerrainChunk(){

}


void TerrainChunk::draw(){
  if(!is_ready){
    if(!gen_thread.joinable()){
      gen_thread = std::thread(generateChunk,this);
    }
  }
  else{
    if(gen_thread.joinable()){
      gen_thread.join();
    }
    mesh.draw();
  }
}

Mesh& TerrainChunk::getMesh(){
  return mesh;
}

/**
\brief static threaded chunk generator. It has no interaction with OpenGL so it should be threadsafe
\param t --- Terrain chunk pointer.
*/
void TerrainChunk::generateChunk(TerrainChunk* t){
  float rgbc = 1/255.0;
  glm::vec3 grass = glm::vec3(0.3764,0.73725, 0.545);
  glm::vec3 snow = glm::vec3(212, 230, 221)*rgbc;
  glm::vec3 water = glm::vec3(96.0/255,130.0/255, 204.0/255);
  glm::vec3 dirt = glm::vec3(83, 56, 45) *rgbc;
  glm::vec3 stone = glm::vec3(164, 164, 163) * rgbc;

  int snow_thresh = 20;
  int grass_thresh = 2;
  int dirt_thresh = -6;
  int water_thresh = -6;


  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  HeightGenerator hg;
  hg.setSeed(t->getSeed());
  hg.setRoughness(0.15);
  hg.setOctaves(4);
  float amp = 40;
  hg.setAmplitude(amp);

  //Copy all of our variables out of our class.
  int cx = t->cx;
  int cz = t->cz;
  unsigned int side_vertices = t->side_vertices;
  unsigned int chunk_size = t->chunk_size;
  int sv = side_vertices+4;
  for(int i = 0; i<sv; i++){
    for(int j = 0; j<sv; j++){
      Vertex vertex;
      //We need a ratio for side vertices and chunk size.
      float ratio = chunk_size/(side_vertices-1);
      float vx = float(j)*ratio;
      float vz = float(i)*ratio;
      float height = hg.generateHeight(j+(cx*chunk_size),i+(cz*chunk_size));

      vertex.position = glm::vec4(vx,height,vz,1);

      if(height>snow_thresh)
        vertex.color = snow;
      else if(height > grass_thresh)
        vertex.color = grass;
      else if(height > dirt_thresh)
        vertex.color = dirt;
      else if(height < water_thresh){
        vertex.color = water;
      }
      else{
        vertex.color = glm::vec3(0);
      }
      vertex.normal = glm::vec3(0,1,0);
      vertices.push_back(vertex);
    }
  }
  for(unsigned int i=0; i<sv-1; i++){
    for(unsigned int j=0; j<sv-1; j++){
      int tl = i*(sv) + j;
      int tr = tl+1;
      int bl = (i+1)*(sv) + j;
      int br = bl+1;
      indices.push_back(tl);
      indices.push_back(bl);
      indices.push_back(tr);
      indices.push_back(tr);
      indices.push_back(bl);
      indices.push_back(br);
    }
  }
  t->mesh.setVertices(vertices);
  t->mesh.setIndices(indices);
  t->setReady(true);
}
