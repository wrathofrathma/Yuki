#include "Drawable.hpp"

Drawable::Drawable(AssetManager *am){
  asset_manager = am;
  vPosition = 0;
  vNormal = 1;
  vColor = 2;
  vTexture = 3;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &dataPtr);
  glGenBuffers(1, &indicePtr);
}

Drawable::~Drawable(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &dataPtr);
  glDeleteBuffers(1, &indicePtr);
}
void Drawable::setUseTexture(bool use){
  shader->bind();
  shader->setBool("useTexture", use);
  useTexture = use;
}
AssetManager *Drawable::getAssetManager(){
  return asset_manager;
}

void Drawable::setVertices(std::vector<float> v){
  vertices = v;
  update = true;
}
void Drawable::setIndices(std::vector<unsigned int> ind){
  indices = ind;
  update = true;
}
void Drawable::setTextureUVs(std::vector<float> uvs){
  texture_uvs = uvs;
  update = true;
}
void Drawable::setNormals(std::vector<float> norms){
  normals = norms;
  update = true;

}
void Drawable::setColors(std::vector<float> c){
  colors = c;
  update = true;
}

void Drawable::setVertices(float* v, unsigned int count){
  vertices.clear();
  vertices = std::vector<float>(v, v+count);
  update = true;
}

void Drawable::setIndices(unsigned int* ind, unsigned int count){
  indices.clear();
  indices = std::vector<unsigned int>(ind, ind+count);
  update = true;
}

void Drawable::setTextureUVs(float* uvs, unsigned int count){
  texture_uvs.clear();
  texture_uvs = std::vector<float>(uvs, uvs+count);
  update = true;
}

void Drawable::setNormals(float* norms, unsigned int count){
  normals.clear();
  normals = std::vector<float>(norms, norms+count);
  update = true;
}

void Drawable::setColors(float* c, unsigned int count){
  colors.clear();
  colors = std::vector<float>(c, c+count);
  update = true;
}


void Drawable::addTexture(std::vector<Texture*> texts){
  for(Texture *t : texts)
    textures.push_back(t);
}
void Drawable::addTexture(Texture* text){
    textures.push_back(text);
}

void Drawable::updateGraphicsCard(){
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

void Drawable::setMaterial(Material mat){
  material = mat;
}
