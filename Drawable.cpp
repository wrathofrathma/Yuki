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
