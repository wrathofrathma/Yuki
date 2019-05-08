#ifndef TEST_CUBE_HPP
#define TEST_CUBE_HPP
#include "../components/Drawable.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "Quad.hpp"
#include "../../AssetManager.hpp"
#include "../components/QuaternionObject.hpp"
#include "../GraphicsDefinitions.hpp"
// This class will double as a cube map when we use it on a giant scale.
class TestCube : QuaternionObject {
  protected:
    bool update;
    AssetManager *asset_manager;
    std::vector<Quad*> faces;
  public:
    TestCube(AssetManager *am);
    ~TestCube();
    void draw();
    void setTexture(std::vector<Texture*> texts);
    void rotate(glm::vec3 rotation);
    void translate(glm::vec3 offset, bool relative=true);
    void scale(glm::vec3 delta);
};

#endif
