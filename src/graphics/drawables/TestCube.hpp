#ifndef TEST_CUBE_HPP
#define TEST_CUBE_HPP
#include "../components/Drawable.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "../components/Drawable.hpp"
#include "../GraphicsDefinitions.hpp"

class AssetManager;
class Texture;
/**
\file TestCube.hpp
\brief Header file for TestCube.cpp

\author Christopher Arausa
\version 0.1 Alpha
\date 5/8/2019

*/



/**
\class TestCube
\brief The TestCube class is an object made for my COSC482 class at Salisbury university for creating a cube that has rotating face textures.

This is accomplished by using multiple indice VBOs and binding a new texture for each face/vbo drawing. Then using a shader that adds a time value to the x component of the texture uv.
*/
class TestCube : public Drawable {
  protected:
    GLuint vbo1, vbo2, vbo3, vbo4, vbo5, vbo6; ///< VBOs for each face.
    std::vector<unsigned int> ind1, ind2, ind3, ind4, ind5, ind6; ///< Indices storage for each face.

  public:
    TestCube(AssetManager *am);
    ~TestCube();
    void draw();
    void setTexture(std::vector<Texture*> texts);
    void updateGraphicsCard();
    void generateCube();
    glm::vec3 rotate_vector;
    void setRotateVector(glm::vec3 r);
    void rotate();
};

#endif
