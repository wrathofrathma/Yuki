#include "HeightGenerator.hpp"
#include "../AssetManager.hpp"
// #include "Firefly.hpp"
#include "../graphics/drawables/Quad.hpp"
#include <random>
#include "../graphics/ObjModel.hpp" // also fetches mesh.
#include "../graphics/components/Light.hpp"
#include <cstdlib>
#include <ctime>
#include "Grass.hpp"
#include "TerrainChunk.hpp"

TerrainChunk::TerrainChunk(AssetManager* am, int x, int z, unsigned int seed, unsigned int chunk_size, unsigned int side_vertices){
  if(seed!=0)
    this->seed = seed;
  else{
    srand(time(nullptr));
    seed = rand() % 100000 + 1;
  }
  this->asset_manager = am;

  textures.push_back(asset_manager->getTexture("grass1"));
  textures.push_back(asset_manager->getTexture("dirt1"));

  mesh.setTexture(textures);
  mesh.setShader(asset_manager->getShader("Terrain"));
  mesh.setMaterial(Materials::Default);
  // water_mesh.setMaterial(Materials::Default);
  // water_mesh.setShader(asset_manager->getShader("Terrain"));
  // water_mesh.setTexture(textures);
  // water_mesh.setUseTexture(true);
  //Chunk x & z coordinates.
  cx = x;
  cz = z;

  //mesh.scale(glm::vec3(1.03,0,1.03));
  is_ready = false;
  this->side_vertices = side_vertices;
  this->chunk_size = chunk_size;
  mesh.setPosition(glm::vec3(x*(chunk_size-2),0,z*(chunk_size-2)));
  // water_mesh.setPosition(glm::vec3(x*(chunk_size-2),0,z*(chunk_size-2)));
  waterQ = new Water(am);
  waterQ->setPosition(glm::vec3(x*(chunk_size-2),-5,z*(chunk_size-2)));
  waterQ->scale(glm::vec3(chunk_size*2));
  waterQ->setMaterial(Materials::Default);
  // waterQ->setShader("Water");
   //waterQ->setTexture(asset_manager->getTexture("water1"));
  waterQ->tex_id = am->reflection_texture;
  waterQ->setUseTexture(true);
  // water_quad = new Quad(am);
  // water_quad->setPosition(glm::vec3(x*(chunk_size-2),-6,z*(chunk_size-2)));
  // water_quad->scale(glm::vec3(chunk_size));
  // water_quad->setMaterial(Materials::Default);
  // water_quad->rotate(glm::vec3(0,PI/2,0));
  // water_quad->setTexture(asset_manager->getTexture("water1"));
  grass.setShader(asset_manager->getShader("Grass"));
  grass.setChunkPos(cx,cz, chunk_size);
  vector<Texture*> grass_texts;
  grass_texts.push_back(asset_manager->getTexture("grass4"));
  grass.setTexture(grass_texts);
}

TerrainChunk::~TerrainChunk(){
  // if(water_quad!=nullptr)
  //   delete water_quad;
  delete waterQ;

}

glm::vec2 TerrainChunk::getPosition(){
  return glm::vec2(cx,cz);
}


void TerrainChunk::draw(bool draw_w){
  if(!is_ready){
    if(!gen_thread.joinable()){
      gen_thread = std::thread(generateChunk,this);
    }
  }
  else{
    if(gen_thread.joinable()){
      gen_thread.join();
    }

    if(draw_w){
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      waterQ->draw();
      //glDepthFunc(GL_LESS);

      glDisable(GL_BLEND);
    }

    grass.draw();
    mesh.draw();
    // glEnable(GL_BLEND);
  // glDepthFunc(GL_LEQUAL);
      // glDepthFunc(GL_LESS);
    // glDisable(GL_BLEND);
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
  std::vector<float> grass_vertices;
  float rgbc = 1/255.0;
  glm::vec3 grass = glm::vec3(0.3764,0.73725, 0.545);
  glm::vec3 snow = glm::vec3(212, 230, 221)*rgbc;
  glm::vec3 water = glm::vec3(96.0/255,130.0/255, 204.0/255);
  glm::vec3 dirt = glm::vec3(83, 56, 45) *rgbc;
  glm::vec3 stone = glm::vec3(164, 164, 163) * rgbc;

  int snow_thresh = 20;
  int grass_thresh = 2;
  int dirt_thresh = -6;
  int water_level = -6;
  std::vector<Vertex> water_mesh_vertices;
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  HeightGenerator hg;
  hg.setSeed(t->getSeed());
  hg.setRoughness(0.10);
  hg.setOctaves(4);
  float amp = 70;
  hg.setAmplitude(amp);

  //Copy all of our variables out of our class.
  int cx = t->cx;
  int cz = t->cz;
  unsigned int side_vertices = t->side_vertices;
  unsigned int chunk_size = t->chunk_size;
  unsigned int water_side_verts = side_vertices / 8;
  int sv = side_vertices;
  for(int i = 0; i<sv; i++){
    for(int j = 0; j<sv; j++){
      Vertex vertex;
      //Ratio between chunk size and side vectors.
      float ratio = chunk_size/(side_vertices-1);
      //Generate terrain mesh.
      float vx = float(j)*ratio;
      float vz = float(i)*ratio;
      float height = hg.generateHeight(j+(cx*chunk_size),i+(cz*chunk_size));
      vertex.position = glm::vec4(vx,height,vz,1);
      t->heights[j][i] = height;
      //Generate water mesh.
      //This is pretty wasteful, but we're in a hurry.

      // if(int(vx) % water_side_verts==0 && int(vz) % water_side_verts == 0){
        Vertex wv;
        wv.position = glm::vec4(vx,water_level,vz,1);
        wv.color = water;
        wv.normal = glm::vec3(0,1,0);
        water_mesh_vertices.push_back(wv);
      // }
      //Coloring, this is honestly more for show since I started doing stuff in the shaders, but it looks cool when we turn stuff off.
      if(height > grass_thresh-1){
        if(height > grass_thresh)
          vertex.color = grass;
        grass_vertices.push_back(vx);
        grass_vertices.push_back(height);
        grass_vertices.push_back(vz);
        grass_vertices.push_back(1);

      }
      // else if(height < water_level)
      //   vertex.color = water;
      else{
        vertex.color = dirt;
      }
      vertex.normal = glm::vec3(0,1,0);
      vertices.push_back(vertex);
    }
  }
  std::vector<unsigned int> water_inds;
  for(int i=0; i<sv-1; i++){
    for(int j=0; j<sv-1; j++){
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
  // for(int i=0; i<water_side_verts-1; i++){
  //   for(int j=0; j<water_side_verts-1; j++){
  //     int tl = i*(water_side_verts) + j;
  //     int tr = tl+1;
  //     int bl = (i+1)*(water_side_verts) + j;
  //     int br = bl+1;
  //     water_inds.push_back(tl);
  //     water_inds.push_back(bl);
  //     water_inds.push_back(tr);
  //     water_inds.push_back(tr);
  //     water_inds.push_back(bl);
  //     water_inds.push_back(br);
  //   }
  // }
  t->mesh.setVertices(vertices);
  t->mesh.setIndices(indices);

  // t->water_mesh.setVertices(water_mesh_vertices);
  // t->water_mesh.setIndices(indices);
  t->setReady(true);
  t->grass.setPoints(grass_vertices);
}

float TerrainChunk::getHeight(int x, int z){
  //Convert to chunk coords.
  cout << x << " " << z << endl;
  cout << "Height: " << heights[z][x] << endl;
  return heights[z][x];
}
