#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <vector>
enum TextureType {
  CubeMap,
  Single
};

class Texture {
  private:
    TextureType type;
    bool loaded;
    std::vector<sf::Image> texture_images;
    GLuint texID;
    int width;
    int height;
    std::string _filename;
  public:
    Texture(std::string filename);
    Texture(std::vector<std::string> filenames);
    ~Texture();
    TextureType getType();
    bool isLoaded();
    GLuint getID();
    std::string getFilename();
};

#endif
