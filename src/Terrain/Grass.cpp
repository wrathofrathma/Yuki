#include "../graphics/Shader.hpp"
#include "../graphics/Texture.hpp"
#include "Grass.hpp"
#include <sstream>
#include <string>
using namespace std;

/**
\file Grass.cpp
\brief Implementation file for GrassPatch class

\author Christopher Arausa
\date 05/14/2019
\version Final
\*/

/**
\brief Constructor

Initializes a single point
*/
GrassPatch::GrassPatch(){
  shader = nullptr;
  ready = false;
  useTexture = false;
  material = Materials::greenTint;
  vPosition = 0;
  vOffset = 1;
  //Single point.
  vertices.push_back(0);
  vertices.push_back(0);
  vertices.push_back(0);
  vertices.push_back(0);
  //
  // vertices.push_back(1);
  // vertices.push_back(0);
  // vertices.push_back(0);
  // vertices.push_back(1);
  //
  // vertices.push_back(1);
  // vertices.push_back(1);
  // vertices.push_back(0);
  // vertices.push_back(1);
  //
  // vertices.push_back(1);
  // vertices.push_back(1);
  // vertices.push_back(0);
  // vertices.push_back(1);
  //
  // vertices.push_back(0);
  // vertices.push_back(1);
  // vertices.push_back(1);
  // vertices.push_back(1);
  //
  // vertices.push_back(0);
  // vertices.push_back(0);
  // vertices.push_back(0);
  // vertices.push_back(0);
}

/**
\brief Destructor

releases memory from gpu
*/
GrassPatch::~GrassPatch(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &instance_buffer);

}

/**
\brief Sets the grass's chunk position

\param cx --- chunk x coordinate
\param cz --- chunk z cooardinate
\param cs --- chunk size
*/

void GrassPatch::setChunkPos(int cx, int cz, int cs){
  position = glm::vec3(cx*(cs-2), 0, cz*(cs-2));
}


/**
\brief Draws the grass patch using instanced rendering
*/
void GrassPatch::draw(){
  if(shader==nullptr)
    return;
  if(!ready)
    init(); //We want to make sure we do the allocation for gpu space in the draw loop so we don't fuck with opengl and threading.
  shader->bind();
  generateModelMatrix();
  shader->setMat4(uModel, model_matrix);
  // shader->setBool("lighting_on", lighting_on);
  //setUseTexture(useTexture);
  //loadMaterial();
  //Upload the points to teh gpu
  shader->setFloat("time", clock.getElapsedTime().asSeconds());
  if(textures.size()>0){
    shader->setBool("useTexture", true);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]->getID());
    //Insert alpha channels later.
  }
  else{
    shader->setBool("useTexture",false);
  }
  glBindVertexArray(VAO);
  glDrawArraysInstanced(GL_POINTS, 0, points.size()/4, 1);
  glBindVertexArray(0);
}

/**
\brief Sets the points to draw the grass at

\param p --- The vector of float points.
*/
void GrassPatch::setPoints(std::vector<float> p){
  points = p;
}

/**
\brief Sets the shader to use

\param shader --- The shader pointer.
*/
void GrassPatch::setShader(Shader* shader){
  this->shader = shader;
  if(shader!=nullptr){
  shader->bind();
    texture_0 = glGetUniformLocation(shader->getID(), "texture_0");
  }
  // texture_1 = glGetUniformLocation(shader->getID(), "texture_1");
  // texture_0 = shader->getUniformLocation("texture_0");
  // texture_1 = shader->getUniformLocation("texture_1");
}


/**
\brief Sets the texture
\param texts --- vector of texture pointers.
*/
void GrassPatch::setTexture(std::vector<Texture*> texts){
  textures = texts;

}

/**
\brief initializes the grass on the gpu
*/
void GrassPatch::init(){
  shader->bind();
  uModel = shader->getUniformLocation("model");

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &vertex_buffer);
  glGenBuffers(1, &instance_buffer);
  glBindVertexArray(0);

  glBindVertexArray(VAO);
  //Upload our object to the buffer.
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);


  glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
  glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);


  glEnableVertexAttribArray(vPosition); //position
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(vOffset);
  glVertexAttribPointer(vOffset, 4, GL_FLOAT, GL_FALSE, 0, (void *)(vertices.size()*sizeof(float)));
  glVertexAttribDivisor(vOffset,1);
  ready = true;
}
