#ifndef CUBE_HPP
#define CUBE_HPP
#include "../QuaternionObject.hpp"
#include "../Texture.hpp"
#include <string>

enum CubeType {
  CUBE_MAP,
  TEXTURED,
  COLORED
};

// This class will double as a cube map when we use it on a giant scale.
class Cube : public QuaternionObject {
  protected:
    Texture *texture;
    CubeType type;

  public:
    Cube();
    ~Cube();

};

#endif
