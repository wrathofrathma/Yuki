#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>

class Texture {
  private:
    bool loaded;
    sf::Image texture_image;
    GLuint texID;
    int width;
    int height;
    std::string _filename;
  public:
    Texture(std::string filename);
    ~Texture();

    bool isLoaded();
    GLuint getID();
    std::string getFilename();
};

#endif
