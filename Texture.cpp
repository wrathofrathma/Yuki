#include "Texture.hpp"
#include <iostream>
using namespace std;

Texture::Texture(std::string filename){
  loaded = texture_image.loadFromFile(filename);
  _filename = filename;
  if(loaded){
    texture_image.flipVertically();
    glGenTextures(1, &texID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.getSize().x, texture_image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);

    height = texture_image.getSize().y;
    width = texture_image.getSize().x;
  }
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
