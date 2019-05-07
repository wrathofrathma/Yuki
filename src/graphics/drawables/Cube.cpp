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
  float vv[] = { //vertices
    -0.5, 0.5, -0.5, 1, //Back upper left
    -0.5, -0.5, -0.5, 1, //Back lower left
    0.5, -0.5, -0.5, 1, //Back lower right
    0.5, 0.5, -0.5, 1, //Back upper right

    -0.5, 0.5, 0.5, 1, //front upper left
    -0.5, -0.5, 0.5, 1, //front lower left
    0.5, -0.5, 0.5, 1, //front lower right
    0.5, 0.5, 0.5, 1 //front upper right
    };

   float vc[] = { //colors
    1, 0, 0,
    0, 1, 0,
    0, 0, 1,
    1, 1, 0,
    0, 1, 1,
    1, 0, 1,
    1, 1, 1,
    0, 0, 0
  };
  //Indices, let's draw the faces in counter clockwise order and in order of the faces for a cube map.
  //Right left top bottom front back
  unsigned int vi[] = {
    //Back
    1, 2, 3,
    3, 0, 1,
    //front
    5, 6, 7,
    7, 4, 5,
    //left
    4, 0, 1,
    1, 5, 4,
    //Right
    7, 3, 2,
    2, 6, 7,
    //Bottom
    1, 2, 6,
    6, 5, 1,
    //top
    0, 3, 7,
    7, 4, 0
  };
  float vn[] = {
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,

    0, 0, -1,
    0, 0, -1,
    0, 0, -1,
    0, 0, -1,

    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,

    0, -1, 0,
    0, -1, 0,
    0, -1, 0,
    0, -1, 0,

    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,

    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0
  };
  setIndices(vi, 36);
  setVertices(vv, 32);
  setColors(vc, 24);
  setNormals(vn, 12*6);
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
