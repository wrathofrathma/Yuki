#include "Drawable.hpp"

Drawable::Drawable(AssetManager *am){
  asset_manager = am;

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
  glBufferSubData(GL_ARRAY_BUFFER, vertice_size + color_size, text_size, &texture_uvs[0]);

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
