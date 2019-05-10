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
  mesh.setShader(asset_manager->getShader("Default"));

  mesh.setMaterial(Materials::Default);
  //Chunk x & z coordinates.
  cx = x;
  cz = z;

  mesh.setPosition(glm::vec3(x*32,0,z*32));
}

TerrainChunk::~TerrainChunk(){

}


void TerrainChunk::draw(){
  if(!is_ready){
    if(!gen_thread.joinable()){
      cout << "Generating chunk generation thread" << endl;
      gen_thread = std::thread(generateChunk,this);
    }
  }
  else{
    if(gen_thread.joinable()){
      cout << "Joining chunk generation thread" << endl;
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
  std::mt19937_64 g1(38383);
  std::uniform_real_distribution<float> dis(0.0,1.0);
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  HeightGenerator hg;
  hg.setSeed(t->getSeed());
  hg.setRoughness(0.2);
  hg.setAmplitude(10);

  for(int i = 0; i<=32 ; i++){
    for(int j = 0; j<=32 ; j++){
      Vertex vertex;
      float height = hg.generateHeight((t->cx*32)+i,(t->cz*32)+j);
      vertex.position = glm::vec4(i,height,j,1.0);
      vertex.color = glm::vec3(dis(g1),dis(g1),dis(g1));
      if(t->cx==0 || t->cz==0)
        vertex.color*=0.0;
      vertex.normal = glm::vec3(0,1,0);
      vertices.push_back(vertex);
    }
  }
  for(unsigned int i=0; i<32; i++){
    for(unsigned int j=0; j<32; j++){
      int tl = i*33 + j;
      int tr = tl+1;
      int bl = (i+1)*33 + j;
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
