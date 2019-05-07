#include "Cube.hpp"
Cube::Cube(AssetManager *am) : Drawable(am){

  shader = am->getShader("Default");
  orientation = glm::vec3(0,0,0);
  setUseTexture(false);
  uModel = shader->getUniformLocation("model");

  generateCube();
  update = true;
}

Cube::~Cube(){

}

void Cube::generateCube(){

  float vv[] = {
    // positions
    -0.5f, -0.5f, -0.5f, 1,
    0.5f, -0.5f, -0.5f, 1,
    0.5f,  0.5f, -0.5f, 1,
    0.5f,  0.5f, -0.5f, 1,
    -0.5f,  0.5f, -0.5f, 1,
    -0.5f, -0.5f, -0.5f, 1,

    -0.5f, -0.5f,  0.5f, 1,
    0.5f, -0.5f,  0.5f, 1,
    0.5f,  0.5f,  0.5f, 1,
    0.5f,  0.5f,  0.5f, 1,
    -0.5f,  0.5f,  0.5f, 1,
    -0.5f, -0.5f,  0.5f, 1,

    -0.5f,  0.5f,  0.5f, 1,
    -0.5f,  0.5f, -0.5f, 1,
    -0.5f, -0.5f, -0.5f, 1,
    -0.5f, -0.5f, -0.5f, 1,
    -0.5f, -0.5f,  0.5f, 1,
    -0.5f,  0.5f,  0.5f, 1,

    0.5f,  0.5f,  0.5f, 1,
    0.5f,  0.5f, -0.5f, 1,
    0.5f, -0.5f, -0.5f, 1,
    0.5f, -0.5f, -0.5f, 1,
    0.5f, -0.5f,  0.5f, 1,
    0.5f,  0.5f,  0.5f, 1,

    -0.5f, -0.5f, -0.5f, 1,
    0.5f, -0.5f, -0.5f, 1,
    0.5f, -0.5f,  0.5f, 1,
    0.5f, -0.5f,  0.5f, 1,
    -0.5f, -0.5f,  0.5f,1,
    -0.5f, -0.5f, -0.5f, 1,

    -0.5f,  0.5f, -0.5f, 1,
    0.5f,  0.5f, -0.5f, 1,
    0.5f,  0.5f,  0.5f, 1,
    0.5f,  0.5f,  0.5f, 1,
    -0.5f,  0.5f,  0.5f, 1,
    -0.5f,  0.5f, -0.5f, 1
  };
  float vn[] = {
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f
  };
  srand(time(nullptr));
  float vc[90];
  for(int i=0; i<90; i++){
    vc[i] = (rand() % 100)/100.0;
  }

  unsigned int vi[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11,
    12, 13, 14,
    15, 16, 17,
    18, 19, 20,
    21, 22, 23,
    24, 25, 26,
    27, 28, 29,
    30, 31, 32,
    33, 34, 35
  };

  setIndices(vi, 36);
  setVertices(vv, 6*24);
  setColors(vc, 30*3);
  setNormals(vn, 24*6);
}

void Cube::draw(){
  initDraw();

  glBindVertexArray(VAO);
  if(useTexture && textures[0]->getType()==CubeMap){
    glBindTexture(GL_TEXTURE_CUBE_MAP, textures[0]->getID());
  }
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
//Sets either one texture for all faces, or is a cube map.
void Cube::setTexture(Texture* text){
  //Set our shader first.
  if(text->getType()==CubeMap){
    shader = asset_manager->getShader("CubeMap");
    textures.clear();
    textures.push_back(text);
  }
  else {
    shader = asset_manager->getShader("Default");
    textures.clear();
    textures.push_back(text);
  }

  setUseTexture(true);
}

//Sets a texture to every face in the order of
//Right Left Top Bottom Back Front
void Cube::setTexture(std::vector<Texture*> texts){

}
