#include "HeightGenerator.hpp"
#include "../AssetManager.hpp"
#include "TerrainChunk.hpp"
#include <random>

#include <cstdlib>
#include <ctime>
TerrainChunk::TerrainChunk(AssetManager* am, int x, int z, unsigned int seed){
  if(seed!=0)
    this->seed = seed;
  else{
    srand(time(nullptr));
    seed = rand() % 100000 + 1;
  }
  this->asset_manager = am;
  setShader(asset_manager->getShader("Default"));

  material = Materials::Default;
  //Chunk x & z coordinates.
  cx = x;
  cz = z;
  hg.setSeed(seed);
  hg.setRoughness(0.2);
  hg.setAmplitude(10);
  generateChunk();
  setPosition(glm::vec3(x*32,0,z*32));
}

TerrainChunk::~TerrainChunk(){

}




void TerrainChunk::generateChunk(){
  int vcount = 32*32;
  std::mt19937_64 g1(38383);
  std::uniform_real_distribution<float> dis(0.0,1.0);

  // for(int i = cx*32; i<(cx*32)+32 ; i++){
  //   for(int j = cz*32; j<(cz*32)+32 ; j++){
  for(int i = 0; i<32 ; i++){
    for(int j = 0; j<32 ; j++){
      Vertex vertex;
      float height = hg.generateHeight((cx*32)+i,(cz*32)+j);
      vertex.position = glm::vec4(i,height,j,1.0);
      vertex.color = glm::vec3(dis(g1),dis(g1),dis(g1));
      vertex.normal = glm::vec3(0,1,0);
      vertices.push_back(vertex);
    }
  }
  for(unsigned int i=0; i<31; i++){
    for(unsigned int j=0; j<31; j++){
      int tl = i*32 + j;
      int tr = tl+1;
      int bl = (i+1)*32 + j;
      int br = bl+1;
      indices.push_back(tl);
      indices.push_back(bl);
      indices.push_back(tr);
      indices.push_back(tr);
      indices.push_back(bl);
      indices.push_back(br);
    }
  }

  update = true;
}
