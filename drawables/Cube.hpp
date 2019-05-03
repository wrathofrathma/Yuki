#ifndef CUBE_HPP
#define CUBE_HPP
#include "../Drawable.hpp"
#include "../Texture.hpp"
#include <string>
#include "../Shader.hpp"
enum CubeTextureType {
  CUBE_MAP,
  TEXTURED,
  COLORED
};

// This class will double as a cube map when we use it on a giant scale.
class Cube : public Drawable {
  protected:
    bool skybox; ///< This setting sets this as a skybox. Which restricts some of the movement and translation events.
    void generateCube();

    bool update;
  public:
    Cube(AssetManager *am);
    ~Cube();
    void draw();
    void updateGraphicsCard();
};

#endif
