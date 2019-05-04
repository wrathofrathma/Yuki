#include "Cube.hpp"
Cube::Cube(AssetManager *am) : Drawable(am){

  shader = am->getShader("2DBasic");
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
    -0.5, 0.5, 0.5, 1,
    -0.5, -0.5, 0.5, 1,
    0.5, -0.5, 0.5, 1,
    0.5, 0.5, 0.5, 1,

    -0.5, 0.5, -0.5, 1,
    -0.5, -0.5, -0.5, 1,
    0.5, -0.5, -0.5, 1,
    0.5, 0.5, -0.5, 1,

    -0.5, 0.5, 0.5, 1,
    -0.5, 0.5, -0.5, 1,
    0.5, 0.5, -0.5, 1,
    0.5, 0.5, 0.5, 1,

    -0.5, -0.5, 0.5, 1,
    -0.5, -0.5, -0.5, 1,
    0.5, -0.5, -0.5, 1,
    0.5, -0.5, 0.5, 1,

    0.5, -0.5, 0.5, 1,
    0.5, -0.5, -0.5, 1,
    0.5, 0.5, -0.5, 1,
    0.5, 0.5, 0.5, 1,

    -0.5, -0.5, 0.5, 1,
    -0.5, -0.5, -0.5, 1,
    -0.5, 0.5, -0.5, 1,
    -0.5, 0.5, 0.5, 1,
    };
   float vc[] = { //colors
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    1, 1, 0,
    1, 1, 0,
    1, 1, 0,
    1, 1, 0,
    0, 1, 1,
    0, 1, 1,
    0, 1, 1,
    0, 1, 1,
    1, 0, 1,
    1, 0, 1,
    1, 0, 1,
    1, 0, 1,
  };

  unsigned int vi[] = {0, 1, 2, //indicies
    2, 3, 0,
    6, 5, 4,
    4, 7, 6,
    10, 9, 8,
    8, 11, 10,
    12, 13, 14,
    14, 15, 12,
    16, 17, 18,
    18, 19, 16,
    22, 21, 20,
    20, 23, 22
  };
  setIndices(vi, 36);
  setVertices(vv, 24*6);
  setColors(vc, 24*3);
}

void Cube::draw(){
  generateModelMatrix();
  shader->setMat4(uModel, model_matrix);
  setUseTexture(useTexture);

  if(update){
    updateGraphicsCard();
  }
  shader->bind();

  if(useTexture && textures.size() > 0){
    glBindTexture(GL_TEXTURE_CUBE_MAP, textures[0]->getID());
  }
  glBindVertexArray(VAO);
  //glDepthMask(GL_TRUE);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
