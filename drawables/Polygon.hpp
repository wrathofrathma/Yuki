#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "../Drawable.hpp"
#include "../Shader.hpp"
#include "../GraphicsDefinitions.hpp"
#include "../Texture.hpp"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // value ptr
#include <vector>
#include <iostream>

using namespace std;

class Polygon : public Drawable {
  protected:

  public:
    Polygon(AssetManager *am);
    ~Polygon();

    void draw();
    GLuint const getVAO();
    unsigned int getVertexCount();
    void setColor(float r, float g, float b);
    void setColor(std::vector<float> c);
    void loadVertices(vector<float> _vertices, vector<unsigned int> _indices);
    void updateGraphicsCard();
    void setTexture(Texture *tex);

};
#endif
