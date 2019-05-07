#ifndef CUBE_HPP
#define CUBE_HPP
#include "../Drawable.hpp"
#include <string>
enum CubeTextureType {
  CUBE_MAP,
  TEXTURED,
  COLORED
};

// This class will double as a cube map when we use it on a giant scale.
class Cube : public Drawable {
  protected:
    void generateCube();

    bool update;
  public:
    Cube(AssetManager *am);
    ~Cube();
    void draw();
    void setTexture(Texture* text);
    void setTexture(std::vector<Texture*> texts);
};

#endif
