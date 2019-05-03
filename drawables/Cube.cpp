#include "Cube.hpp"
Cube::Cube(AssetManager *am) : Drawable(am){
  asset_manager = am;
  vPosition = 0;
  vColor = 1;
  vTexture = 2;
  texture = nullptr;

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

void Cube::updateGraphicsCard(){
  unsigned int vertice_size = vertices.size() * sizeof(float);
  unsigned int color_size = colors.size() * sizeof(float);
  unsigned int text_size = texture_coords.size() * sizeof(float);
  unsigned int indice_size = indices.size() * sizeof(unsigned int);
  unsigned int data_size = text_size + color_size + vertice_size;

  glBindVertexArray(VAO);
  //Load indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_size, &indices[0], GL_DYNAMIC_DRAW);

  //Allocate space for data
  glBindBuffer(GL_ARRAY_BUFFER, dataPtr);
  glBufferData(GL_ARRAY_BUFFER, data_size, NULL, GL_DYNAMIC_DRAW);

  //Load data as parts of sub partitions of the buffer
  //vertices
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertice_size, &vertices[0]);
  //Color
  glBufferSubData(GL_ARRAY_BUFFER, vertice_size, color_size, &colors[0]);
  //Texture
  glBufferSubData(GL_ARRAY_BUFFER, vertice_size + color_size, text_size, &texture_coords[0]);

  //Tell the shader how to find its data
  glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertice_size + color_size));
  glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(vertice_size));
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glEnableVertexAttribArray(vPosition);
  glEnableVertexAttribArray(vColor);
  glEnableVertexAttribArray(vTexture);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  update = false;
}
void Cube::draw(){
  glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(generateModelMatrix()));
  setUseTexture(useTexture);

  if(update){
    updateGraphicsCard();
  }

  shader->bind();
  if(useTexture){
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getID());
  }
  glBindVertexArray(VAO);
  glDepthMask(GL_TRUE);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
