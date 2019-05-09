#include "TestCube.hpp"
#include "../../AssetManager.hpp"
#include "../Texture.hpp"
#include <iostream>
using namespace std;

/**
\file TestCube.cpp
\brief Implementation of the TestCube class.

\author    Christopher Arausa
\version   0.1
\date      05/8/2019

*/

/**
\brief Constructor

Generates 6 VBOs for indices, sets the shader to the Rotate shader, and material to default.
\param am --- AssetManager class pointer.
*/
TestCube::TestCube(AssetManager *am) : Drawable(am){
  asset_manager = am;
  shader = am->getShader("Rotate");
  orientation = glm::vec3(0,0,0);
  setUseTexture(true);
  uModel = shader->getUniformLocation("model");
  glGenBuffers(1, &vbo1);
  glGenBuffers(1, &vbo2);
  glGenBuffers(1, &vbo3);
  glGenBuffers(1, &vbo4);
  glGenBuffers(1, &vbo5);
  glGenBuffers(1, &vbo6);
  glDeleteBuffers(1,&indicePtr);
  generateCube();
  setMaterial(Materials::Default);
  update = true;
}

/**
\brief Destructor

Deletes the buffers allocated on the graphics card.
*/
TestCube::~TestCube(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &dataPtr);
  glDeleteBuffers(1, &vbo1);
  glDeleteBuffers(1, &vbo2);
  glDeleteBuffers(1, &vbo3);
  glDeleteBuffers(1, &vbo4);
  glDeleteBuffers(1, &vbo5);
  glDeleteBuffers(1, &vbo6);
}

/**
\brief Draws the cube.

Inbetween each glDrawElements call, we change the bound indice buffer and bind a new texture.
*/
void TestCube::draw(){
  initDraw();

  glBindVertexArray(VAO);
  glBindTexture(GL_TEXTURE_2D, textures[0]->getID());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo1);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindTexture(GL_TEXTURE_2D, textures[1]->getID());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo2);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindTexture(GL_TEXTURE_2D, textures[2]->getID());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo3);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindTexture(GL_TEXTURE_2D, textures[3]->getID());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo4);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindTexture(GL_TEXTURE_2D, textures[4]->getID());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo5);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindTexture(GL_TEXTURE_2D, textures[5]->getID());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo6);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

/**
\brief Sets the textures of the cube.

If the vector doesn't contain 6 textures we return without doing anything.
\param texts --- Texture pointer vector to use.
*/
void TestCube::setTexture(std::vector<Texture*> texts){
  if(texts.size() < 6)
    return;
  textures = texts;
}

/**
\brief Generates the cube.

Similar to the normal cube generator I have, this one separates the indices into 6 different buffers and sets the texture uvs.
*/
void TestCube::generateCube(){

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
  float vc[36*3];
  for(int i=0; i<36*3; i++){
    vc[i] = (rand() % 100)/100.0;
  }

  unsigned int vi1[] = {
    0, 1, 2,
    3, 4, 5
  };
  unsigned int vi2[] = {
    6, 7, 8,
    9, 10, 11
  };
  unsigned int vi3[] = {
    12, 13, 14,
    15, 16, 17
  };
  unsigned int vi4[] = {
    18, 19, 20,
    21, 22, 23
  };
  unsigned int vi5[] = {
    24, 25, 26,
    27, 28, 29
  };
  unsigned int vi6[] = {
    30, 31, 32,
    33, 34, 35
  };

  ind1 = std::vector<unsigned int>(vi1, vi1+6);
  ind2 = std::vector<unsigned int>(vi2, vi2+6);
  ind3 = std::vector<unsigned int>(vi3, vi3+6);
  ind4 = std::vector<unsigned int>(vi4, vi4+6);
  ind5 = std::vector<unsigned int>(vi5, vi5+6);
  ind6 = std::vector<unsigned int>(vi6, vi6+6);

  for(int i=0; i<6; i++){
  texture_uvs.push_back(0);
  texture_uvs.push_back(0);
  texture_uvs.push_back(0);
  texture_uvs.push_back(1);
  texture_uvs.push_back(1);
  texture_uvs.push_back(1);
  texture_uvs.push_back(1);
  texture_uvs.push_back(1);
  texture_uvs.push_back(1);
  texture_uvs.push_back(0);
  texture_uvs.push_back(0);
  texture_uvs.push_back(0);
}

  setVertices(vv, 6*24);
  setColors(vc, 36*3);
  setNormals(vn, 24*6);
}

/**
\brief Uploads the cube data to the graphics card.

The only change here is in the number of VBOs we upload.
*/
void TestCube::updateGraphicsCard(){
  unsigned int vertice_size = vertices.size() * sizeof(float);
  unsigned int color_size = colors.size() * sizeof(float);
  unsigned int text_size = texture_uvs.size() * sizeof(float);

  unsigned int normal_size = normals.size() * sizeof(float);
  unsigned int data_size = text_size + color_size + vertice_size + normal_size;

  glBindVertexArray(VAO);
  //Load indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo1);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(float), &ind1[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo2);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(float), &ind2[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo3);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(float), &ind3[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo4);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(float), &ind4[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo5);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(float), &ind5[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo6);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(float), &ind6[0], GL_DYNAMIC_DRAW);

  //Allocate space for data
  glBindBuffer(GL_ARRAY_BUFFER, dataPtr);
  glBufferData(GL_ARRAY_BUFFER, data_size, NULL, GL_DYNAMIC_DRAW);

  //Load data as parts of sub partitions of the buffer
  //vertices
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertice_size, &vertices[0]);
  //Color
  glBufferSubData(GL_ARRAY_BUFFER, vertice_size, color_size, &colors[0]);
  //Texture
  glBufferSubData(GL_ARRAY_BUFFER, vertice_size + color_size, text_size, &texture_uvs[0]);
  //Normals
  glBufferSubData(GL_ARRAY_BUFFER, vertice_size + color_size + text_size, normal_size, &normals[0]);
  //Tell the shader how to find its data
  glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertice_size + color_size));
  glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(vertice_size));
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertice_size + color_size + text_size));

  glEnableVertexAttribArray(vPosition);
  glEnableVertexAttribArray(vColor);
  glEnableVertexAttribArray(vNormal);
  glEnableVertexAttribArray(vTexture);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  update = false;
}

/**
\brief Rotate function to rotate by the same stored rotation vector when called.
*/
void TestCube::rotate(){
  QuaternionObject::rotate(rotate_vector);
}

/**
\brief Sets the vector to rotate by when we call rotate().
\param r --- glm::vec3 containing the axis to rotate on.
*/
void TestCube::setRotateVector(glm::vec3 r){
  rotate_vector = r;
}
