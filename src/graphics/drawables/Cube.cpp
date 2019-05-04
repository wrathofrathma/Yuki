#include "Cube.hpp"
Cube::Cube(AssetManager *am) : Drawable(am){
  asset_manager = am;
  vPosition = 0;
  vColor = 1;
  vTexture = 2;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &dataPtr);
  glGenBuffers(1, &indicePtr);
  glGenTextures(1, &tex);

  shader = am->getShader("2DBasic");
  orientation = glm::vec3(0,0,0);
  setUseTexture(false);

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
  indices = std::vector<unsigned int>(vi, vi+36);
  vertices = std::vector<float>(vv, vv+24*6);
  colors = std::vector<float>(vc, vc+24*3);
}

void Cube::draw(){
  glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(generateModelMatrix()));
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
