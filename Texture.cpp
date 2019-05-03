#include "Texture.hpp"
#include <iostream>
using namespace std;

Texture::Texture(std::string filename){
  type = Single;
  texture_images.emplace_back(sf::Image());
  loaded = texture_images[0].loadFromFile(filename);
  _filename = filename;
  if(loaded){
    texture_images[0].flipVertically();
    glGenTextures(1, &texID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_images[0].getSize().x, texture_images[0].getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_images[0].getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);

    height = texture_images[0].getSize().y;
    width = texture_images[0].getSize().x;
  }
}

Texture::Texture(std::vector<std::string> filenames){
  type = CubeMap;
  loaded = false;
  _filename = "";
  if(filenames.size()!=6)
    return;

  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

  for(unsigned int i = 0; i<6; i++){
    _filename+=","+filenames[i];
    texture_images.emplace_back(sf::Image());
    loaded = texture_images[i].loadFromFile(filenames[i]);
    if(!loaded)
      return;
    texture_images[i].flipVertically();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texture_images[i].getSize().x, texture_images[i].getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_images[i].getPixelsPtr());
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

TextureType Texture::getType(){
  return type;
}
Texture::~Texture(){

}

bool Texture::isLoaded(){
  return loaded;
}

GLuint Texture::getID(){
  return texID;
}

std::string Texture::getFilename(){
  return _filename;
}
