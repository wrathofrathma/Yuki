#include "../Texture.hpp"
#include "../Material.hpp"
#include "../Shader.hpp"
#include "Mesh.hpp"

/**
\file Mesh.cpp
\brief Implementation of the Mesh class.

\author Christopher Arausa
\version 0.1
\date 5/10/2019

*/
#include <iostream>
using namespace std;
Mesh::Mesh(){
  vPosition = 0;
  vNormal = 1;
  vColor = 2;
  vTexture = 3;
  shader = nullptr;
  lighting_on = true;
  useTexture = false;

}
Mesh::Mesh(Mesh&m1){

  vPosition = 0;
  vNormal = 1;
  vColor = 2;
  vTexture = 3;
  setShader(m1.getShader());
  setLightingOn(m1.getLightingOn());
  useTexture = false;
  setVertices(m1.getVertices());
  setNormals(m1.getNormals());
  setColors(m1.getColors());
  setTextureUVs(m1.getUVS());
  setTexture(m1.getTextures());
  setIndices(m1.getIndices());
  update = true;
  cout << "Vertices: " << vertices.size() << endl;
  cout << "Normals: " << normals.size() << endl;
  cout << "UVs: " << texture_uvs.size() << endl;
  cout << "Indicies: " << indices.size() << endl;
}
std::vector<Texture*> Mesh::getTextures(){
  return textures;
}

std::vector<float> Mesh::getUVS(){
  return texture_uvs;
}

std::vector<float> Mesh::getNormals(){
  return normals;
}

std::vector<float> Mesh::getVertices(){
  return vertices;
}

std::vector<float> Mesh::getColors(){
  return colors;
}

std::vector<unsigned int> Mesh::getIndices(){
  return indices;
}

Shader* Mesh::getShader(){
  return shader;
}
Mesh::~Mesh(){
  cleanup();
}


/**
\brief Calculates model matrix, sets shader uniforms and then draws the mesh.
*/
void Mesh::draw(){
  //If we didn't set the shader then we don't need to really do anything.
  if(shader==nullptr)
    return;
  shader->bind();
  //If our mesh has changed we need to upload it again.
  if(update){
    updateMesh();
    loadTextures();
  }
  //Generating model matrix.
  generateModelMatrix();
  //Updating uniforms.
  shader->setMat4(uModel, model_matrix);
  shader->setBool("lighting_on", lighting_on);
  shader->setBool("useTexture", useTexture);

  loadMaterial();

  glm::mat3 normal_matrix = glm::mat3(glm::transpose(glm::inverse(model_matrix)));
  shader->setMat3("normal_matrix", normal_matrix);
  //Now we actually draw whatever.
  if(useTexture){
    for(unsigned int i=0; i<textures.size(); i++){
      glActiveTexture(GL_TEXTURE0+i);
      std::string s_loc = "textures[" + std::to_string(i) + "]";
      glBindTexture(GL_TEXTURE_2D,textures[i]->getID());
    }
    glActiveTexture(GL_TEXTURE0);
  }
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
/**
\brief Loads all vertice, color, texture, indice, and normal data to the graphics card.
*/
void Mesh::updateMesh(){
  unsigned int vertice_size = vertices.size() * sizeof(float);
  unsigned int color_size = colors.size() * sizeof(float);
  unsigned int text_size = texture_uvs.size() * sizeof(float);
  unsigned int indice_size = indices.size() * sizeof(unsigned int);
  unsigned int normal_size = normals.size() * sizeof(float);
  unsigned int data_size = text_size + color_size + vertice_size + normal_size;

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

void Mesh::updateVertices(std::vector<float> vs){
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, dataPtr);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), &vertices[0]);
  // glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}

/**
\brief Loads the material data to the shader.
*/
void Mesh::loadMaterial(){
  shader->bind();
  glm::vec4 amb = material.getAmbient();
  glm::vec4 diff = material.getDiffuse();
  glm::vec4 spec = material.getSpecular();
  glm::vec4 emis = material.getEmission();
  shader->setVec4("material.ambient",amb);
  shader->setVec4("material.diffuse", diff);
  shader->setVec4("material.specular",spec);
  shader->setFloat("material.shininess",material.getShininess());
  shader->setVec4("material.emission",emis);
}
/**
\brief Loads the textures to the shader.
*/
void Mesh::loadTextures(){
  shader->bind();
  for(int i=0; i<=textures.size() &&  i<10; i++){
    std::string s_loc = "textures[" + std::to_string(i) + "]";
    gl_textures[i] = shader->getUniformLocation(s_loc);
    shader->setInt(gl_textures[i], (i));
  }
}

/**
\brief Tells the class to bind a texture on the draw loop and sets the uniform on our shader for if we're using a texture.
\param use --- The boolean value to set for if we're using a texture.
*/
void Mesh::setUseTexture(bool use){
  useTexture = use;
}
/**
\brief Releases VAO/VBO/EBO data on the graphics card.
*/
void Mesh::cleanup(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &dataPtr);
  glDeleteBuffers(1, &indicePtr);
}


void Mesh::setTexture(std::vector<Texture*> textures){
  this->textures = textures;
  update=true;
  useTexture = true;
}
/**
\brief Sets the shader to use directly by setting the shader.
\param shader --- Pointer to the shader to use.
*/
void Mesh::setShader(Shader* shader){
  this->shader = shader;
  if(shader!=nullptr){
    cleanup();
    update = true;
    shader->bind();
    uModel = shader->getUniformLocation("model");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &dataPtr);
    glGenBuffers(1, &indicePtr);
  }
  update = true;
}

unsigned int Mesh::getVertexCount(){
  return vertices.size();
}

/**
\brief Sets whether to apply lighting to this object.
\param onoff --- Boolean value to use.
*/
void Mesh::setLightingOn(bool onoff){
  lighting_on = onoff;
}
/**
\brief Returns whether to apply lighting to this object.
*/
bool Mesh::getLightingOn(){
  return lighting_on;
}

void Mesh::setMaterial(Material mat){
  material = mat;
}

/**
\brief Sets all data to do with vertices. Vertices, normals, colors, and texture uvs.
\param vertices --- Vector of Vertice structs.
*/
void Mesh::setVertices(std::vector<Vertex> vertices){
  this->vertices.clear();
  this->colors.clear();
  this->normals.clear();
  this->texture_uvs.clear();
  for(unsigned int i=0; i<vertices.size(); i++){
    this->vertices.push_back(vertices[i].position.x);
    this->vertices.push_back(vertices[i].position.y);
    this->vertices.push_back(vertices[i].position.z);
    this->vertices.push_back(vertices[i].position.w);

    this->colors.push_back(vertices[i].color.x);
    this->colors.push_back(vertices[i].color.y);
    this->colors.push_back(vertices[i].color.z);

    this->normals.push_back(vertices[i].normal.x);
    this->normals.push_back(vertices[i].normal.y);
    this->normals.push_back(vertices[i].normal.z);

    this->texture_uvs.push_back(vertices[i].texture.x);
    this->texture_uvs.push_back(vertices[i].texture.y);
  }
  update = true;
}
/**
\brief Sets our vertice data for the object and marks our update flag.
\param v --- Vertex array data to use.
\param count --- Number of elements in the array.
*/
void Mesh::setVertices(float* v, unsigned int count){
  vertices.clear();
  vertices = std::vector<float>(v, v+count);
  update = true;
}
/**
\brief Sets our vertice data for the object and marks our update flag.
\param v --- Vertice data vector to use.
*/
void Mesh::setVertices(std::vector<float> v){
  vertices = v;
  update = true;
}

/**
\brief Sets our indice data for the object and marks our update flag.
\param ind --- Indice data vector to use.
*/
void Mesh::setIndices(std::vector<unsigned int> ind){
  indices = ind;
  update = true;
}
/**
\brief Sets our indice data for the object and marks our update flag.
\param ind --- Indice array data to use.
\param count --- Number of elements in the array.
*/
void Mesh::setIndices(unsigned int* ind, unsigned int count){
  indices.clear();
  indices = std::vector<unsigned int>(ind, ind+count);
  update = true;
}


/**
\brief Sets our normal data for the object and marks our update flag.
\param norms --- Normal data vector to use.
*/
void Mesh::setNormals(std::vector<float> norms){
  normals = norms;
  update = true;
}

/**
\brief Sets our normal data for the object and marks our update flag.
\param norms --- Normal array data to use.
\param count --- Number of elements in the array.
*/
void Mesh::setNormals(float* norms, unsigned int count){
  normals.clear();
  normals = std::vector<float>(norms, norms+count);
  update = true;
}

/**
\brief Sets our texture uv data for the object and marks our update flag.
\param uvs --- Texture UV array data to use.
\param count --- Number of elements in the array.
*/
void Mesh::setTextureUVs(float* uvs, unsigned int count){
  texture_uvs.clear();
  texture_uvs = std::vector<float>(uvs, uvs+count);
  update = true;
}
/**
\brief Sets our texture uv data for the object and marks our update flag.
\param uvs --- Texture UV data vector to use.
*/
void Mesh::setTextureUVs(std::vector<float> uvs){
  texture_uvs = uvs;
  update = true;
}

/**
\brief Sets our color data for the object and marks our update flag.
\param c --- Color array data to use.
\param count --- Number of elements in the array.
*/
void Mesh::setColors(float* c, unsigned int count){
  colors.clear();
  colors = std::vector<float>(c, c+count);
  update = true;
}

/**
\brief Sets our color data for the object and marks our update flag.
\param c --- Color data vector to use.
*/
void Mesh::setColors(std::vector<float> c){
  colors = c;
  update = true;
}
